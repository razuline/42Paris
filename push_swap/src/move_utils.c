/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erazumov <erazumov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/13 17:23:50 by erazumov          #+#    #+#             */
/*   Updated: 2025/04/19 12:06:13 by erazumov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/push_swap.h"

t_node	*create_node(int value)
{
	t_node	*new_node;

	new_node = (t_node *)malloc(sizeof(t_node));
	if (!new_node)
		return (NULL);
	new_node->value = value;
	new_node->index = -1;
	new_node->prev = NULL;
	new_node->next = NULL;
	return (new_node);
}

int	node_position(t_stack *stack, t_node *node_to_find)
{
	t_node	*current;
	int		pos;

	if (!stack || !node_to_find || !stack->head)
		return (-1);
	pos = 0;
	current = stack->head;
	while (current)
	{
		if (current == node_to_find)
			return (pos);
		pos++;
		current = current->next;
	}
	return (-1);
}

void	node_to_top_a(t_stack *stack_a, t_node *target_node)
{
	int	pos;
	int	size;
	int	fwd;
	int	rev;

	if (!stack_a || stack_a->size < 2 || !target_node
		|| stack_a->head == target_node)
		return ;
	pos = node_position(stack_a, target_node);
	if (pos == -1)
		return ;
	size = stack_a->size;
	fwd = pos;
	rev = size - pos;
	if (fwd <= rev)
	{
		while (fwd-- > 0)
			ra(stack_a);
	}
	else
	{
		while (rev-- > 0)
			rra(stack_a);
	}
}

void	node_to_top_b(t_stack *stack_b, t_node *target_node)
{
	int	pos;
	int	size;
	int	fwd;
	int	rev;

	if (!stack_b || stack_b->size < 2 || !target_node
		|| stack_b->head == target_node)
		return ;
	pos = node_position(stack_b, target_node);
	if (pos == -1)
		return ;
	size = stack_b->size;
	fwd = pos;
	rev = size - pos;
	if (fwd <= rev)
	{
		while (fwd-- > 0)
			rb(stack_b);
	}
	else
	{
		while (rev-- > 0)
			rrb(stack_b);
	}
}
