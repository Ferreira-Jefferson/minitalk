#include "libft/libft.h"
#include <signal.h>
#include <unistd.h>
#include <stdio.h>

void handle_signal(int signal, siginfo_t *info, void *content)
{
	(void) content;
	(void) info;

	if (signal == SIGUSR1 || signal == SIGUSR2)
	{
		ft_printf("The server message was receive.\n");
		exit(0);
	}
}

int main(int argc, char *argv[])
{
	pid_t pid;
	pid_t pid_server;
	struct sigaction sa;

	if (argc <= 2)
		return ft_printf("Expected: program_name PID_server message.\n");
	if (argc > 3)
		return ft_printf("Many arguments.\n");

	pid = getpid();
	ft_printf("PID client: %d\n", pid);

	pid_server = ft_atoi(argv[1]);
	if(!pid_server)
		return ft_printf("Expected: program_name PID_server message.\n");
	
	kill(pid_server, SIGUSR1);
	kill(pid_server, SIGUSR2);

	sa.sa_sigaction = handle_signal;
	sa.sa_flags = SA_SIGINFO;
	sigaction(SIGUSR2, &sa, NULL);

	while (1)
		pause();
	return (0);
}