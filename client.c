#include "libft/libft.h"
#include <signal.h>
#include <unistd.h>
#include <limits.h>

volatile sig_atomic_t next = 1;

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
		usleep(100);
	}
}

static void	ft_send_message_bits(pid_t server_pid, unsigned int message)
{
	size_t len;
	len = 8;
	while (len--)
	{
		if (message % 2)
			kill(server_pid, SIGUSR2);
		else
			kill(server_pid, SIGUSR1);
		message >>= 1;
		usleep(500);
	}
}

static void	ft_send_message(unsigned int client_pid, unsigned int server_pid, char *message)
{
	static unsigned int client_pid_aux;
	static unsigned int server_pid_aux;
	static char *message_aux;

	if (!client_pid_aux)
	{
		client_pid_aux = client_pid;
		server_pid_aux = server_pid;
		message_aux = message;
		ft_send_pid_bits(server_pid_aux, client_pid);
	}
	if (*message_aux)
		ft_send_message_bits(server_pid_aux, *message_aux++);
	else
		ft_send_message_bits(server_pid_aux, '\0');
}

void handle_next(int signal)
{
	if (signal == SIGUSR2)
		next = 1;
}

void handle_exit(int signal)
{
	if (signal == SIGUSR1)
	{
		ft_printf("The server message was received.\n");
		exit(0);
	}
}

int main(int argc, char *argv[])
{
	pid_t				pid_client;
	pid_t				pid_server;

	if (argc != 3)
		return ft_printf("Expected: %s <PID_server> <message>\n", argv[0]);
	pid_client = getpid();
	ft_printf("PID client: %d\n", pid_client);
	pid_server = ft_atoi(argv[1]);
	if (!pid_server)
		return ft_printf("Invalid PID.\n");
	
	signal(SIGUSR1, handle_exit);
	signal(SIGUSR2, handle_next);

	while (1)
	{
		ft_send_message(pid_client, pid_server, argv[2]);
		usleep(100);
	}
	return (0);
}
