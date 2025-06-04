/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   safe_atoi.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erazumov <erazumov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 15:07:58 by erazumov          #+#    #+#             */
/*   Updated: 2025/06/04 16:25:34 by erazumov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

static bool	is_space(char c)
{
	return (c == ' ' || c == '\t' || c == '\n' || c == '\v' || c == '\f'
		|| c == '\r');
}

static bool	is_digit(char c)
{
	return (c >= '0' && c <= '9');
}

int	safe_atoi(const char *str, int *result)
{
	int			sign;
	uint64_t	n;

	sign = 1;
	n = 0;
	while (is_space(*str))
		str++;
	if (*str == '+' || *str == '-')
	{
		if (*str == '-')
			sign = -1;
		str++;
	}
	if (!is_digit(*str))
		return (printf("Error: Not a number\n"), false);
	while (is_digit(*str) && n <= INT_MAX)
		n = n *10 + (*str++ - '0');
	if ((n > INT_MAX && sign == 1) || (n - 1 > INT_MAX && sign == -1))
		return (0);
	if (*str && (*str < 9 || *str > 13) && *str != ' ')
		return (0);
	*result = n * sign;
	return (1);
}

/*
int	main(int ac, char **av)
{
	(void)ac;
	int	n;

	if (!safe_atoi(av[1], &n))
		return (printf("Error: Invalid input\n"), 1);
	printf("Parsed: %d\n", n);
}
*/
