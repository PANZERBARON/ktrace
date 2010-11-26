#include <sys/param.h>
#include <sys/uio.h>
#include <sys/time.h>
#include <sys/stat.h>
#include <sys/ktrace.h>
#include <sys/types.h>

#include <unistd.h>

#include "my_ktrace.h"
#include "my_ktrace_optparse.h"
#include "my_ktrace_utils.h"

static int    get_check_points(char *);

struct k_inf	optparser(int argc, char **argv)
{
  int						ch;
  struct k_inf	infos;

	infos = init_infos_struct();
  while ((ch = getopt(argc, argv, "aCcdf:g:ip:t:")) != -1)
    switch(ch)
    {
      case 'a':
        infos.append = YES;
        break;
      case 'C':
        infos.ktrop_mode = STOP_TRACE;
        infos.pidset = YES;
        break;
      case 'c':
        infos.ktrop_mode = DISABLE_STP;
        break;
      case 'd':
        infos.ops |= KTRFLAG_DESCEND;
        break;
      case 'f':
        infos.tracefile = optarg;
        break;
      case 'g':
        infos.pid = ck_pid_mutual_valid(optarg);
        infos.pidset = YES;
        break;
      case 'i':
        infos.inherit = YES;
        break;
      case 'p':
        infos.pid = -ck_pid_mutual_valid(optarg);
        infos.pidset = YES;
        break;
      case 't':
        infos.trpoints = get_check_points(optarg);
        break;
      default:
        usage_error();
    }
  argv += optind;
  argc -= optind;

  if ((*argv && infos.pidset) ||
     (!*argv && !infos.pidset && infos.ktrop_mode != DISABLE_STP))
    usage_error();
  else if (*argv)
		infos.command = argv;
 
  if (infos.inherit)
    infos.trpoints |= KTRFAC_INHERIT;

	return (infos); 
}

static int		get_check_points(char *opt_trpoints)
{
    int trpoints = 0;

		while (*opt_trpoints++)
			switch(*opt_trpoints)
			{
				case 'c':
					trpoints |= (KTRFAC_SYSRET | KTRFAC_SYSCALL); break;
				case 'e':
					trpoints |= KTRFAC_EMUL;  break;
				case 'i':
					trpoints |= KTRFAC_GENIO; break;
				case 'n':
					trpoints |= KTRFAC_NAMEI; break;
				case 's':
					trpoints |= KTRFAC_PSIG;  break;
				case 'w':
					trpoints |= KTRFAC_CSW;   break;
				case '+':
					trpoints |= TR_POINTS;    break;
				default:
					usage_error();
			}
  return (trpoints);
}
