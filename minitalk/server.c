/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erazumov <erazumov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/15 11:19:22 by erazumov          #+#    #+#             */
/*   Updated: 2025/02/15 13:56:10 by erazumov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

static int	bit = 0; /* Track the bit we're currently processing */
static int	char_value = 0; /* Accumulate the character value */

void	signal_handler(int sig)
{
	/* Add the value of the bit at position `bit` by adding 2^bit */
	if (sig == SIGUSR1)
		char_value += (1 << bit); /* Add value of the current bit */
	bit++;

	/* If we've processed all 8 bits (one character) */
	if (bit == 8)
	{
		/* Print the character corresponding to the accumulated bits */
		write(1, &char_value, 1);
		/* Reset bit counter and character accumulator for the next byte */
		bit = 0;
		char_value = 0;
	}
}

#include <stdio.h>

int	main(void)
{
	int	pid;

	pid = getpid();
	printf("Server PID: %d\n", pid);

	signal(SIGUSR1, signal_handler);
	signal(SIGUSR2, signal_handler);
	/* Wait indefinitely for signals */
	while (1)
	{
		pause (); /* Wait for signals to arrive */
	}
	return (0);
}
