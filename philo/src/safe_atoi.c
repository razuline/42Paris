/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   safe_atoi.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erazumov <erazumov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 15:07:58 by erazumov          #+#    #+#             */
/*   Updated: 2025/06/03 15:16:57 by erazumov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static bool	is_space(char c)
{
	return (c == ' ' || c == '\t' || c == '\n'
		|| c == '\v' || c == '\f' || c == '\r');
}

static bool	is_digit(char c)
{
	return (c >= '0' && c <= '9');
}

int	safe_atoi(const char *str, int *result)
{
	int			sign;
	uint64_t	value;

	sign = 1;
	value = 0;
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
	while (is_digit(*str))
	{
		value = value * 10 + (*str - '0');
		if ((sign == 1 && value > INT_MAX)
				|| (sign == -1 && value > -(uint64_t)INT_MIN))
	}
		while (*str >= '0' && *str <= '9')
		{
			result = result * 10 + (*str - '0');
			str++;
		}
	return (result);
}
