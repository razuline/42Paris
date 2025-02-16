/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erazumov <erazumov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/15 11:19:22 by erazumov          #+#    #+#             */
/*   Updated: 2025/02/16 16:05:27 by erazumov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minitalk.h"

void	handler(int signal)
{
	static char	ch;
	static int	bit;

	if (signal == SIGUSR1)
		ch += (1 << bit);
	bit++;
	if (bit == 8)
	{
		ft_printf("%c", ch);
		bit = 0;
		ch = 0;
	}
}

int	main(int ac, char **av)
{
	int	pid;

	(void)av;
	if (ac != 1)
	{
		ft_printf("Error: wrong format.\n");
		ft_printf("Try: ./server\n");
		return (0);
	}
	pid = getpid();
	ft_printf("Server PID: %d\n", pid);
	ft_printf("Waiting for a message...\n");
	while (ac == 1)
	{
		signal(SIGUSR1, handler);
		signal(SIGUSR2, handler);
		pause ();
	}
	return (0);
}
