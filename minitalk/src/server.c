/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erazumov <erazumov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/15 11:19:22 by erazumov          #+#    #+#             */
/*   Updated: 2025/04/10 14:34:19 by erazumov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minitalk.h"

void	handler(int sig, siginfo_t *info, void *context)
{
	static int	bit;
	static char	c;

	(void)context;
	if (sig == SIGUSR1)
		c |= (1 << bit);
	bit++;
	if (bit == 8)
	{
		if (c == '\0')
			ft_printf("\nMessage received from PID: %d\n", info->si_pid);
		else
			ft_printf("%c", c);
		bit = 0;
		c = 0;
	}
	kill(info->si_pid, SIGUSR1);
}

int	main(int ac, char **av)
{
	struct sigaction	sa;

	(void)av;
	if (ac != 1)
	{
		ft_printf("Usage: ./server\n");
		return (1);
	}
	ft_printf("Server PID: %d\n", getpid());
	sa.sa_sigaction = handler;
	sa.sa_flags = SA_SIGINFO;
	sigemptyset(&sa.sa_mask);
	sigaction(SIGUSR1, &sa, NULL);
	sigaction(SIGUSR2, &sa, NULL);
	while (1)
		pause();
	return (0);
}
