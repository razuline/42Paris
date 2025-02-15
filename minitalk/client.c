/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erazumov <erazumov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/15 11:19:30 by erazumov          #+#    #+#             */
/*   Updated: 2025/02/15 14:08:10 by erazumov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

/* The client sends a string to the server by converting each character
	into 8 bits and sending each bit with SIGUSR1 (0) or SIGUSR2 (1).*/

static long int	ft_atoi(const char *str)
{
	int					i;
	int					sign;
	unsigned long int	result;

	i = 0;
	sign = 1;
	result = 0;
	while (str[i] == 32 || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			sign *= -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		result = 10 * result + (str[i] - '0');
		i++;
	}
	return (result * sign);
}

void	send_bit(char c, int pid)
{
	int	bit;
	int	shift;

	/* Go through the bits of the character (8 bits) */
	shift = 7; /* Start from the most significant bit */
	while (shift >= 0)
	{
		bit = (c >> shift) & 1; /* Get bit at the position shift */

		/* Send the bit as a signal */
		if (bit == 1)
			kill(pid, SIGUSR1); /* Send SIGUSR1 for bit 1 */
		else
			kill(pid, SIGUSR2); /* Send SIGUSR2 for bit 0 */

		/* Small delay to ensure the signal is processed correctly */
		usleep(30);
		shift--; /* Move to the next bit */
	}
}

int	main(int ac, char **av)
{
	int			i;
	long int	pid;
	char		*str;

	if (ac != 3)
	{
		write(1, "Usage: ./client <PID> <string>\n", 30);
		return (1);
	}

	pid = ft_atoi(av[1]); /* Convert the first argument (PID) to an integer */
	if (pid <= 0 || pid > 32768) /* PID max */
	{
		write(1, "Invalid PID\n", 12);
		return (1);
	}
	str = av[2]; /* Store the message to send (2nd argument) */

	i = 0;
	while (str[i] != '\0')
	{
		send_bit(str[i], pid);
		i++;
	}

	/* Send string to the server */
	send_bit('\0', pid);

	return (0);
}
