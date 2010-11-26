#ifndef __MY_KTRACE__
# define __MY_KTRACE__

#define TR_POINTS (KTRFAC_SYSCALL | KTRFAC_SYSRET | KTRFAC_NAMEI | \
									KTRFAC_GENIO | KTRFAC_PSIG | KTRFAC_EMUL)
#define DEF_TRACEFILE "ktrace.out"
#define YES 1

struct k_inf
{
		enum {ENABLE_STP, DISABLE_STP, STOP_TRACE} ktrop_mode;
		char *tracefile;
    char **command;
		int		ops;
		int		trpoints;
    int		pid;
		int   pidset;
    int		append;
		int		inherit;		
};

#endif /*_MY_KTRACE_ */
