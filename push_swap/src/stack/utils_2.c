/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erazumov <erazumov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 15:14:16 by erazumov          #+#    #+#             */
/*   Updated: 2025/04/09 15:18:50 by erazumov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../includes/push_swap.h"

int	find_position(t_stack *stack, int value)
{
	t_node	*current;
	int		pos;

	if (!stack || !stack->head)
		return (-1);
	current = stack->head;
	pos = 0;
	while (current)
	{
		if (current->value == value)
			return (pos);
		current = current->next;
		pos++;
	}
	return (-1);
}

int	find_target_position(t_stack *a, int value)
{
	t_node	*current;
	int		target_pos;
	int		min;
	int		max;

	if (!a || !a->head)
		return (0);
	min = find_min(a);
	max = find_max(a);
	if (value < min)
		return (find_position(a, min));
	if (value > max)
		return (find_position(a, max) + 1);
	current = a->head;
	target_pos = 0;
	while (current)
	{
		if (value > current->value && value < current->next->value)
		{
			target_pos = find_position(a, current->next->value);
			break ;
		}
		current = current->next;
	}
	return (target_pos);
}

