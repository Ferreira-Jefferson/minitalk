#include "libft/libft.h"
#include <signal.h>
#include <unistd.h>
#include <limits.h>
#include <stdio.h>

static void	ft_send_length_bits(pid_t server_pid, unsigned int size)
{
	size_t	len;

	len = 6;
	while (len--)
	{
		if (size % 2)
			kill(server_pid, SIGUSR2);
		else
			kill(server_pid, SIGUSR1);
		size >>= 1;
		usleep(200);
	}
}

static void	ft_send_message_bits(pid_t server_pid, unsigned int message, size_t len)
{
	while (len--)
	{
		if (message % 2)
			kill(server_pid, SIGUSR2);
		else
			kill(server_pid, SIGUSR1);
		message >>= 1;
		usleep(200);
	}
}

static void	ft_send_message(unsigned int server_pid, unsigned int client_pid, char *message)
{
	size_t	size;

	size = ft_binary_len(client_pid);
	ft_send_length_bits(server_pid, size);
	ft_send_message_bits(server_pid, client_pid, size);
	while (*message)
	{
		size = ft_binary_len(*message);
		ft_send_length_bits(server_pid, size);
		ft_send_message_bits(server_pid, *message, size);
		message++;
	}
	size = ft_binary_len('\0');
	ft_send_length_bits(server_pid, size);
	ft_send_message_bits(server_pid, '\0', size);
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
