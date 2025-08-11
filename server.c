#include "libft/libft.h"
#include <signal.h>
#include <unistd.h>
#include <stdio.h>

static size_t ft_get_length_bits(int signum, size_t size)
{
	static int		command_size[6];
	unsigned char	length;
	size_t			i;

	length = 0;
	if (size < 6)
		command_size[size++] = (signum == SIGUSR2);
	if (size == 6)
	{
		i = 0;
		while (i < 6)
		{
			length |= (command_size[i] & 1) << i;
			i++;
		}
	}
	return (length);
}

static int *ft_prepare_message(int signum, size_t length, size_t index)
{
	static int		*message;
	static size_t	current_length;

	if (current_length != length)
		message = ft_to_free((void**)&message);
	if (!message)
	{
		current_length = length;
		message = (int *) ft_calloc(length, sizeof(int));
		if (!message)
			return (NULL);
	}
	message[index] = (signum == SIGUSR2);
	if ((index + 1) == length)
		return (message);
	return (NULL);
}

static unsigned int ft_create_value(int *message, size_t length)
{
	unsigned int	number;
	size_t			i;

	number = 0;
	i = 0;
	while (i < length)
	{
		number |= (message[i] & 1) << i;
		i++;
	}
	return (number);
}
/*
static void ft_create_message(size_t *length, int **bit_message, unsigned int *pid_client, char *message, size_t *mess_index)
{
	unsigned int		value;

	value = ft_create_value(*bit_message, *length);
	if (*pid_client == 0)
		*pid_client = value;
	else
	{
		if (value == '\0')
		{
			message[*mess_index] = '\0';
			ft_printf("%s", *message);
			kill(*pid_client, SIGUSR1);
			*mess_index = 0;
			*pid_client = 0;
		}
		else
		{
			(*message)[mess_index] = (char)value;
			(*mess_index)++;
		}
	}
}

*/
void signal_handle(int signum, siginfo_t *info, void *context)
{
	(void) info;
	(void) context;
	static size_t		length;
	static size_t		len;
	static int			*bit_message;
	static unsigned int	pid_client;
	static char			message[1024];
	static size_t		mess_index;
	unsigned int		value;

	if (len < 6 && length == 0)
	{
		length = ft_get_length_bits(signum, len++);
		return;
	}
	bit_message = ft_prepare_message(signum, length, len - 6);
	len++;
	;
	if (bit_message)
	{
		value = ft_create_value(bit_message, length);
		if (pid_client == 0)
			pid_client = value;
		else
		{
			if (value == '\0')
			{
				message[mess_index] = '\0';
				ft_printf("%s", message);
				kill(pid_client, SIGUSR1);
				mess_index = 0;
				pid_client = 0;
			}
			else
				message[mess_index++] = (char)value;
		}
		len = 0;
		length = 0;
	}
}

int	main(void)
{
	pid_t				pid;
	struct sigaction sa;

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
