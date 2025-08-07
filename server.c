#include <signal.h>
#include <unistd.h>
#include <stdio.h>

void signal_handle(int signum, siginfo_t *info, void *context)
{
	//static char *mensage;
	(void) info;
	(void) context;

	if (signum == SIGUSR1)
		printf("0\n");
	else if (signum == SIGUSR2)
		printf("1\n");
} 

int	main(void)
{
	pid_t				pid;
	struct sigaction	sa;

	pid = getpid();
	printf("PID Server: %d\n", pid);

	sa.sa_sigaction = signal_handle;
	sa.sa_flags = SA_SIGINFO;
	sigaction(SIGUSR1, &sa, NULL);
	sigaction(SIGUSR2, &sa, NULL);

	while (1)
		pause();
	return (0);
}