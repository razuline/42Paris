/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parce.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erazumov <erazumov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 18:23:47 by erazumov          #+#    #+#             */
/*   Updated: 2025/04/12 12:42:43 by erazumov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static int	is_num(char *s)
{
	if (*s == '-' || *s == '+')
		s++;
	while (*s)
	{
		if (!ft_isdigit(*s++))
			return (0);
	}
	return (1);
}

static long	push_swap_atol(char *str, t_stack *a, t_stack *b)
{
	long	nb;
	int		sign;

	sign = 1;
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			sign *= -1;
		str++;
	}
	while (*str >= '0' && *str <= '9')
	{
		nb = 0;
		nb = nb * 10 + (*str++ - '0');
		if (nb > INT_MAX || (sign == -1 && nb > (long)INT_MAX + 1))
			error_exit(a, b);
	}
	return (nb * sign);
}

void	parse_args(t_stack *a, t_stack *b, char **av)
{
	char	**split;
	long	num;

	while (*++av)
	{
		split = ft_split(*av, ' ');
		while (split && *split)
		{
			if (!is_num(*split))
				error_exit(a, b);
			num = push_swap_atol(*split, a, b);
			if (num < INT_MIN || num > INT_MAX || is_duplicate(a, num))
				error_exit(a, b);
			add_node(a, num);
			free(*split++);
		}
		free(split);
	}
}
