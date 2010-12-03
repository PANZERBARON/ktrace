#include <sys/types.h>
#include <sys/param.h>
#include <sys/uio.h>
#include <sys/ktrace.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <fstab.h>
#include <stdio.h>
#include <fcntl.h>
#include <errno.h>
#include "my_ktrace.h"
#include "my_ktrace_utils.h"

struct k_inf  init_infos_struct(void) 
{
  struct k_inf infos;

  infos.tracefile  = DEF_TRACEFILE;
  infos.command    = NULL;
  infos.ktrop_mode = ENABLE_STP;
  infos.trpoints   = TR_POINTS;
  infos.ops = 0;
  infos.pidset = 0;
  infos.pid = 0;
  infos.append = 0;
  infos.inherit = 0;

  return (infos);
}

void    check_tracefile(struct k_inf infos)
{
  int     fd = 0;
  mode_t  omask;
  struct  stat sb;

  omask = umask(S_IRWXG|S_IRWXO);
  if (infos.append)
  {
    if ((fd = open(infos.tracefile, O_CREAT | O_WRONLY, DEFFILEMODE)) < 0)
      exit (1);
    if (fstat(fd, &sb) != 0 || sb.st_uid != getuid())
    {
      printf("Refuse to append to %s: not owned by you.",
          infos.tracefile);
      exit (1);
    }
  }
  else
  {
    if (unlink(infos.tracefile) == -1 && errno != ENOENT)
      printf("unlink %s", infos.tracefile);
    if ((fd = open(infos.tracefile, O_CREAT | O_EXCL | O_WRONLY,
        DEFFILEMODE)) < 0)
      exit (1);
  }
  umask(omask);
  close(fd);
}

void    do_ktrace_syscalls(struct k_inf infos)
{
  if (infos.ktrop_mode != ENABLE_STP)
  {
    if (infos.ktrop_mode == STOP_TRACE)
    {
      infos.ops |= KTROP_CLEAR | KTRFLAG_DESCEND;
      infos.trpoints |= TR_POINTS | KTRFAC_CSW;
      infos.pid = 1;
    }
    else
      infos.ops |= infos.pid ? KTROP_CLEAR : KTROP_CLEARFILE;

    if (ktrace(infos.tracefile, infos.ops, infos.trpoints, infos.pid) < 0)
      usage_error();
    exit (0);
  }
  if (infos.command[0])
  {
    if (ktrace(infos.tracefile, infos.ops, infos.trpoints, getpid()) < 0)
      exit (1);
    execvp(infos.command[0], &infos.command[0]);
    printf("exec of '%s' failed", infos.command[0]);
  }
  else if (ktrace(infos.tracefile, infos.ops, infos.trpoints, infos.pid) < 0)
    exit (1);
  exit (0);	
}

void      usage_error(void)
{
  printf("usage: ktrace [-aCcdi] [-f trfile] [-g pgid] [-p pid] [-t trstr]\n"
         "       ktrace [-adi] [-f trfile] [-t trstr] command\n");
  exit(1);
}

int   ck_pid_mutual_valid(char *pid)
{
  static int check_mutual_ok = 0;
  if (check_mutual_ok++ || !*pid)
    usage_error();
  return (atoi(pid));
}

void  no_kernel_compliance(int sign)
{
  printf("%s \n", KERNEL_COMPLIANCE_MSG);
  exit (1);
}
