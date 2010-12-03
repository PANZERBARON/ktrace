#include "my_ktrace.h"
#include "my_ktrace_utils.h"
#include "my_ktrace_optparse.h"

int   main(int argc, char **argv)
{
  struct k_inf  k_info;

  k_info = optparser(argc, argv);
  signal(SIGSYS, no_kernel_compliance);
  check_tracefile(k_info);
  do_ktrace_syscalls(k_info);

  return (0);
}
