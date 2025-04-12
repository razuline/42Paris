/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   positions.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erazumov <erazumov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/12 12:19:05 by erazumov          #+#    #+#             */
/*   Updated: 2025/04/12 12:51:05 by erazumov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	find_min_position(t_stack *stack)
{
	int		min;
	int		pos;
	t_node	*tmp;

	min = find_min(stack);
	pos = 0;
	tmp = stack->head;
	while (tmp)
	{
		if (tmp->value == min)
			return (pos);
		pos++;
		tmp = tmp->next;
	}
	return (0);
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
