#ifndef __MY_KTRACE_UTILS__
# define __MY_KTRACE_UTILS__

struct	k_inf  init_infos_struct(void);
void    check_tracefile(struct k_inf);
void    do_ktrace_syscalls(struct k_inf);
void    usage_error(void);
int			ck_pid_mutual_valid(char *);

#endif
