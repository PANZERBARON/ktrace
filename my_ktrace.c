#include "my_ktrace.h"
#include "my_ktrace_utils.h"
#include "my_ktrace_optparse.h"

int   main(int ac, char **av)
{
  struct k_inf  k_info;

  k_info = optparser(ac, av);
  signal(SIGSYS, no_kernel_compliance);
  check_tracefile(k_info);
  do_ktrace_syscalls(k_info);

  return (0);
}
