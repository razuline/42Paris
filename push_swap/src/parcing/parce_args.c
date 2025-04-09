/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parce_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erazumov <erazumov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 18:30:58 by erazumov          #+#    #+#             */
/*   Updated: 2025/04/09 13:31:28 by erazumov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../includes/push_swap.h"

void	parse_args(t_stack *a, char **av)
{
	int		i;
	int		j;
	int		num;
	char	**split;

	i = 1;
	while (av[i])
	{
		split = ft_split(av[i], ' ');
		if (!split)
			if_error("Error: Memory allocation failed!\n");
		j = 0;
		while (split[j])
		{
			if (!is_valid_number(split[j]))
				if_error("Error: Invalid number!\n");
			num = ft_atoi(split[j]);
			if (is_duplicate(a, num))
				if_error("Error: Duplicate number!\n");
			push_to(a, num);
			free(split[j]);
			j++;
		}
		free(split);
		i++;
	}
}

int	is_valid_number(char *str)
{
	int	i;

	i = 0;
	if (str[i] == '-' || str[i] == '+')
		i++;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
}

int	is_duplicate(t_stack *stack, int value)
{
	t_node	*current;

	current = stack->head;
	while (current)
	{
		if (current->value == value)
			return (1);
		current = current->next;
	}
	return (0);
}
