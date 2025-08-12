#include "libft/libft.h"
#include <signal.h>
#include <unistd.h>
#include <limits.h>
#include <stdio.h>

static void	ft_send_pid_bits(pid_t server_pid, int pid_client)
{
	size_t len = 24;
	while (len--)
	{
		if (pid_client % 2)
			kill(server_pid, SIGUSR2);
		else
			kill(server_pid, SIGUSR1);
		pid_client >>= 1;
		usleep(50);
	}
}

static void	ft_send_message_bits(pid_t server_pid, unsigned int message)
{
	size_t len = 8;
	while (len--)
	{
		if (message % 2)
			kill(server_pid, SIGUSR2);
		else
			kill(server_pid, SIGUSR1);
		message >>= 1;
		usleep(900);
	}
}

static void	ft_send_message(unsigned int server_pid, unsigned int client_pid, char *message)
{
	ft_send_pid_bits(server_pid, client_pid);
	while (*message)
	{
		ft_send_message_bits(server_pid, *message);
		message++;
	}
	ft_send_message_bits(server_pid, '\0');
}

void handle_signal(int signal, siginfo_t *info, void *content)
{
	(void) content;
	(void) info;

	if (signal == SIGUSR1 || signal == SIGUSR2)
	{
		ft_printf("The server message was received.\n");
		exit(0);
	}
}

int main(int argc, char *argv[])
{
	pid_t				pid_client;
	pid_t				pid_server;
	struct sigaction	sa;

	if (argc != 3)
		return ft_printf("Expected: %s <PID_server> <message>\n", argv[0]);
	pid_client = getpid();
	ft_printf("PID client: %d\n", pid_client);
	pid_server = ft_atoi(argv[1]);
	if (!pid_server)
		return ft_printf("Invalid PID.\n");
	sa.sa_sigaction = handle_signal;
	sa.sa_flags = SA_SIGINFO;
	sigemptyset(&sa.sa_mask);
	sigaction(SIGUSR1, &sa, NULL);
	sigaction(SIGUSR2, &sa, NULL);
	ft_send_message(pid_server, pid_client, argv[2]);
	while (1)
		pause();
	return (0);
}
