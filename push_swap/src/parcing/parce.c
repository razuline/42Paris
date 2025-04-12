/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parce.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erazumov <erazumov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 18:23:47 by erazumov          #+#    #+#             */
/*   Updated: 2025/04/12 17:05:37 by erazumov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static void	clean_and_exit(char **split, t_stack *a, t_stack *b)
{
	if (split)
		free_split(split);
	error_exit(a, b);
}

long	push_swap_atol(const char *str, t_stack *a, t_stack *b)
{
	long	num;
	int		sign;
	int		i;

	num = 0;
	sign = 1;
	i = 0;
	while (ft_isspace(str[i]))
		i++;
	if (str[i] == '-' || str[i] == '+')
		sign = (str[i++] == '-') ? -1 : 1;
	if (!ft_isdigit(str[i]))
		clean_and_exit(NULL, a, b);
	while (str[i] >= '0' && str[i] <= '9')
	{
		num = num * 10 + (str[i++] - '0');
		if ((sign == 1 && num > INT_MAX)
				|| (sign == -1 && num > -(long)INT_MIN))
			clean_and_exit(NULL, a, b);
	}
	return (num * sign);
}

void	parse_args(t_stack *a, t_stack *b, char **av)
{
	char	**split;
	char	**tmp;
	long	num;
	int		i;

	i = 0;
	while (av[++i])
	{
		split = ft_split(av[i], ' ');
		if (!split || !*split)
			clean_and_exit(split, a, b);
		tmp = split;
		while (*tmp)
		{
			if (!is_valid_number(*tmp))
				clean_and_exit(split, a, b);
			num = push_swap_atol(*tmp, a, b);
			if (num < INT_MIN || num > INT_MAX || is_duplicate(a, num))
				clean_and_exit(split, a, b);
			add_node(a, num);
			free(*tmp++);
		}
		free(split);
	}
}
