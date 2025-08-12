#include "libft/libft.h"
#include <signal.h>
#include <unistd.h>
#include <stdio.h>

static int ft_handle_pid_client(int signum)
{
	static int pid_vet[24];
	static int index;
	int pid_client;

	if (!signum)
	{
		index = 0;
		return (0);
	}
	pid_vet[index++] = (signum == SIGUSR2);
	if (index == 24)
	{
		pid_client = 0;
		while (index--)
		{
			pid_client <<= 1;
			pid_client |= (pid_vet[index] & 1);
		}
		return (pid_client);
	}
	return (0);
}

static int ft_handle_message(int signum, int index)
{
	static int mess_vet[8];
	static int message;

	if (index == 0)
		message = 0;
	mess_vet[index] = (signum == SIGUSR2);
	if (index == 7)
	{
		message = 0;
		while (index >= 0)
		{
			message <<= 1;
			message |= (mess_vet[index] & 1);
			index--;
		}
		return (message);
	}
	return (0);
}

int ft_print_message(int message)
{
	if (message == '\0')
		return (0);
	ft_printf("%c", message);
	return (-1);
}

void signal_handle(int signum, siginfo_t *info, void *context)
{
	(void) info;
	(void) context;
	static int pid_client;
	static int message;
	static int index;

	if (!pid_client)
		pid_client = ft_handle_pid_client(signum);
	else
	{
		message = ft_handle_message(signum, index++);
		if (index == 8)
		{
			if (!ft_print_message(message))
			{
				kill(pid_client, SIGUSR1);
				pid_client = 0;
				ft_handle_pid_client(0);
			}
			index = 0;
			message = 0;
		}
	}	
}

int	main(void)
{
	pid_t				pid;
	struct sigaction	sa;

	pid = getpid();
	ft_printf("PID Server: %d\n", pid);
	sa.sa_sigaction = signal_handle;
	sa.sa_flags = SA_SIGINFO;
	sigemptyset(&sa.sa_mask);
	sigaction(SIGUSR1, &sa, NULL);
	sigaction(SIGUSR2, &sa, NULL);
	while (1)
		pause();
	return (0);
}
