/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erazumov <erazumov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/15 11:19:30 by erazumov          #+#    #+#             */
/*   Updated: 2025/04/10 14:16:53 by erazumov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minitalk.h"

/* The client sends a string to the server by converting each character
	into 8 bits and sending each bit with SIGUSR1 (0) or SIGUSR2 (1).*/

void	send_char(char c, int pid)
{
	int	bit;

	bit = 0;
	while (bit < 8)
	{
		if ((c & (1 << bit)))
			kill(pid, SIGUSR1);
		else
			kill(pid, SIGUSR2);
		usleep(300);
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
	if (pid <= 0 || kill(pid, 0) == -1)
	{
		ft_printf("Error: Invalid PID\n");
		return (1);
	}
	i = 0;
	while (av[2][i])
		send_char(av[2][i++], pid);
	send_char('\0', pid);
	return (0);
}
