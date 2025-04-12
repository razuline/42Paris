/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parce.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erazumov <erazumov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 18:23:47 by erazumov          #+#    #+#             */
/*   Updated: 2025/04/12 13:14:15 by erazumov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

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

static void	process_number(char *str, t_stack *a, t_stack *b)
{
	long	num;

	num = push_swap_atol(str, a, b);
	if (num < INT_MIN || num > INT_MAX || is_duplicate(a, num))
		error_exit(a, b);
	add_node(a, num);
}

void	parse_args(t_stack *a, t_stack *b, char **av)
{
	char	**split;
	int		i;
	int		j;

	i = 1;
	while (av[i])
	{
		split = ft_split(av[i], ' ');
		if (!split)
			error_exit(a, b);
		j = 0;
		while (split[j])
		{
			process_number(split[j], a, b);
			free(split[j]);
			j++;
		}
		free(split);
		i++;
	}
}
