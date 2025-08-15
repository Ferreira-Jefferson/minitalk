/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtertuli <jtertuli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/15 13:57:00 by jtertuli          #+#    #+#             */
/*   Updated: 2025/08/15 14:04:44 by jtertuli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"
#include <signal.h>
#include <unistd.h>

volatile sig_atomic_t	next = 1;

static void	ft_send_message_bits(pid_t server_pid, unsigned int message)
{
	size_t	len;

	len = 8;
	while (len--)
	{
		next = 0;
		if (message % 2)
			kill(server_pid, SIGUSR2);
		else
			kill(server_pid, SIGUSR1);
		message >>= 1;
		while (!next)
			pause();
	}
}

void	handle_next(int signal)
{
	if (signal == SIGUSR2)
		next = 1;
}

void	handle_exit(int signal)
{
	if (signal == SIGUSR1)
	{
		ft_printf("The server message was received.\n");
		exit(0);
	}
}

void	setup_signal_handlers(void)
{
	struct sigaction	sa_next;
	struct sigaction	sa_exit;

	sa_next.sa_handler = handle_next;
	sigemptyset(&sa_next.sa_mask);
	sa_next.sa_flags = SA_RESTART;
	sigaction(SIGUSR2, &sa_next, NULL);
	sa_exit.sa_handler = handle_exit;
	sigemptyset(&sa_exit.sa_mask);
	sa_exit.sa_flags = SA_RESTART;
	sigaction(SIGUSR1, &sa_exit, NULL);
}

int	main(int argc, char *argv[])
{
	pid_t	pid_server;

	if (argc != 3)
	{
		ft_printf("Expected: %s <PID_server> <message>\n", argv[0]);
		return (1);
	}
	pid_server = ft_atoi(argv[1]);
	if (!pid_server)
	{	
		ft_printf("Invalid PID.\n");
		return (1);
	}
	ft_printf("PID client: %d\n", getpid());
	setup_signal_handlers();
	while (1)
	{
		ft_send_message_bits(pid_server, *argv[2]);
		if (*argv[2] == '\0')
			break ;
		argv[2]++;
	}
	ft_send_message_bits(pid_server, '\0');
	return (0);
}
