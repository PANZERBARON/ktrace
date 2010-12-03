#ifndef __MY_KTRACE_UTILS__
# define __MY_KTRACE_UTILS__

#include <signal.h>

#define KERNEL_COMPLIANCE_MSG "Your kernel hasn't been compiled to ktrace support."

struct  k_inf  init_infos_struct(void);
void           check_tracefile(struct k_inf);
void           do_ktrace_syscalls(struct k_inf);
void           usage_error(void);
int            ck_pid_mutual_valid(char *);
void           no_kernel_compliance(int);

#endif
