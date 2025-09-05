/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erazumov <erazumov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/05 18:11:26 by erazumov          #+#    #+#             */
/*   Updated: 2025/09/05 18:35:22 by erazumov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* (HELPER) to initialize conversion: handles whitespace and sign. */
static const char	*atoll_init(const char *str, int *sign)
{
	while (*str == ' ' || (*str >= '\t' && *str <= '\r'))
		str++;
	*sign = 1;
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			*sign = -1;
		str++;
	}
	return (str);
}

/* (HELPER) The conversion loop and overflow detection. */
static int	atoll_convert(const char *str, unsigned long long *acc)
{
	unsigned long long	cutoff;
	unsigned long long	cutlim;

	cutoff = LLONG_MAX / 10;
	cutlim = LLONG_MAX % 10;
	*acc = 0;
	while (*str >= '0' && *str <= '9')
	{
		if (*acc > cutoff || (*acc == cutoff
			&& (unsigned long long)(*str - '0') > cutlim))
			return (0);
		*acc = *acc * 10 + (*str - '0');
		str++;
	}
	while (*str == ' ' || (*str >= '\t' && *str <= '\r'))
		str++;
	if (*str != '\0')
		return (0);
	return (1);
}

/* Converts a string to a long long and checks for overflows. */
int	ft_atoll_check(const char *str, long long *n)
{
	int					sign;
	unsigned long long	acc;

	str = atoll_init(str, &sign);
	if (sign == -1)
	{
		if (atoll_convert(str, &acc) == 0 || acc
			> (unsigned long long)LLONG_MIN * -1)
			return (0);
	}
	else
	{
		if (atoll_convert(str, &acc) == 0 || acc > LLONG_MAX)
			return (0);
	}
	if (sign == 1)
		*n = (long long)acc;
	else
		*n = -(long long)acc;
	return (1);
}
