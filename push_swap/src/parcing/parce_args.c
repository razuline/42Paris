/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parce_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erazumov <erazumov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 18:30:58 by erazumov          #+#    #+#             */
/*   Updated: 2025/04/09 15:39:14 by erazumov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../includes/push_swap.h"

static int	validate_number(char *str)
{
	int	i;

	i = 0;
	if (str[i] == '-' || str[i] == '+')
		i++;
	if (!str[i])
		return (0);
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
}

static void	handle_number(t_stack *a, char *str)
{
	long	num;

	if (!validate_number(str))
		if_error("Error");
	num = ft_atol(str);
	if (num < INT_MIN || num > INT_MAX)
		if_error("Error");
	if (is_duplicate(a, (int)num))
		if_error("Error");
	push_to(a, (int)num);
}

static void	process_arg(t_stack *a, char *arg)
{
	char	**split;
	int		i;

	split = ft_split(arg, ' ');
	if (!split)
		if_error("Error");
	i = 0;
	while (split[i])
	{
		handle_number(a, split[i]);
		free(split[i]);
		i++;
	}
	free(split);
}

void	parse_args(t_stack *a, char **av)
{
	int	i;

	i = 1;
	while (av[i])
	{
		process_arg(a, av[i]);
		i++;
	}
}
