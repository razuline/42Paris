/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erazumov <erazumov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/15 11:19:30 by erazumov          #+#    #+#             */
/*   Updated: 2025/04/10 14:50:58 by erazumov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minitalk.h"

/* The client sends a string to the server by converting each character
	into 8 bits and sending each bit with SIGUSR1 (0) or SIGUSR2 (1).*/

static volatile sig_atomic_t	g_ack_received = 0;

static void	ack_handler(int sig)
{
	(void)sig;
	g_ack_received = 1;
}

static void	send_bit(int bit, int pid)
{
	int	timeout;

	g_ack_received = 0;
	if (bit)
		kill(pid, SIGUSR1);
	else
		kill(pid, SIGUSR2);
	timeout = 1000;
	while (!g_ack_received && --timeout > 0)
		usleep(100);
	if (timeout == 0)
		ft_printf("Error: Server did not respond!\n");
}

void	send_char(char c, int pid)
{
	int	bit;

	bit = 0;
	while (bit < 8)
	{
		send_bit((c >> bit) & 1, pid);
		bit++;
	}
}

int	main(int ac, char **av)
{
	int	pid;
	int	i;

	if (ac != 3)
	{
		ft_printf("Usage: ./client <PID> <message>\n");
		return (1);
	}
	pid = ft_atoi(av[1]);
	signal(SIGUSR1, ack_handler);
	i = 0;
	while (av[2][i])
		send_char(av[2][i++], pid);
	send_char('\0', pid);
	return (0);
}
