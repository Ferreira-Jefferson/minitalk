#include "libft/libft.h"
#include <signal.h>
#include <unistd.h>
#include <stdio.h>

pid_t	client_pid = 0;

static int	ft_handle_message(int signum)
{
	static int	mess_vet[8];
	static int	message;
	static int	index;

	mess_vet[index++] = (signum == SIGUSR2);
	if (index == 8)
	{
		message = 0;
		while (index > 0)
		{
			index--;
			message <<= 1;
			message |= (mess_vet[index] & 1);
		}
		if (message == '\0')
			kill(client_pid, SIGUSR1);
		return (message);
	}
	kill(client_pid, SIGUSR2);
	return (0);
}

void	signal_handle(int signum, siginfo_t *info, void *context)
{
	static int	message;

	(void) context;
	client_pid = info->si_pid;
	message = ft_handle_message(signum);
	if (message)
	{
		ft_printf("%c", message);
		message = 0;
		kill(client_pid, SIGUSR2);
	}
}

void	setup_signal_handlers(void)
{
	struct sigaction	sa;

	sa.sa_sigaction = signal_handle;
	sa.sa_flags = SA_SIGINFO;
	sigemptyset(&sa.sa_mask);
	sigaction(SIGUSR1, &sa, NULL);
	sigaction(SIGUSR2, &sa, NULL);
}

int	main(void)
{
	pid_t	pid;

	setup_signal_handlers();
	pid = getpid();
	ft_printf("PID Server: %d\n", pid);
	while (1)
		pause();
	return (0);
}
