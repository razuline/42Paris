/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   positions.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erazumov <erazumov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/12 12:19:05 by erazumov          #+#    #+#             */
/*   Updated: 2025/04/12 16:33:43 by erazumov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	find_min(t_stack *stack)
{
	int		min;
	t_node	*current;

	if (!stack || !stack->head)
		return (INT_MAX);
	min = stack->head->value;
	current = stack->head->next;
	while (current)
	{
		if (current->value < min)
			min = current->value;
		current = current->next;
	}
	return (min);
}

int	find_min_pos(t_stack *stack)
{
	int		min;
	int		pos;
	int		min_pos;
	t_node	*current;

	if (!stack || !stack->head)
		return (0);
	min = find_min(stack);
	pos = 0;
	min_pos = 0;
	current = stack->head;
	while (current)
	{
		if (current->value == min)
		{
			min_pos = pos;
			break ;
		}
		current = current->next;
		pos++;
	}
	return (min_pos);
}

int	find_second_min(t_stack *stack)
{
	t_node	*current;
	int		min;
	int		second_min;

	min = find_min_pos(stack);
	second_min = INT_MAX;
	current = stack->head;
	while (current)
	{
		if (current->value > min && current->value < second_min)
			second_min = current->value;
		current = current->next;
	}
	return (second_min);
}

int	find_target_pos(t_stack *a, int val)
{
	t_node	*node;
	int		pos;

	pos = 0;
	node = a->head;
	while (node && node->value < val)
	{
		pos++;
		node = node->next;
	}
	return (pos);
}

void	while_pos(t_stack *s, int pos, int rev)
{
	while (pos-- > 0)
	{
		if (rev)
			rra(s);
		ra(s);
	}
}
