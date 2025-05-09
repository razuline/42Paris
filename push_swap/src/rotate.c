/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotate.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erazumov <erazumov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/13 13:42:50 by erazumov          #+#    #+#             */
/*   Updated: 2025/04/13 13:44:57 by erazumov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/push_swap.h"

static void	rotate_stack(t_stack *stack)
{
	t_node	*first;
	t_node	*second;

	if (!stack || stack->size < 2)
		return ;
	first = stack->head;
	second = first->next;
	stack->tail->next = first;
	first->prev = stack->tail;
	first->next = NULL;
	second->prev = NULL;
	stack->head = second;
	stack->tail = first;
}

void	ra(t_stack *stack_a)
{
	if (!stack_a || stack_a->size < 2)
		return ;
	rotate_stack(stack_a);
	write(1, "ra\n", 3);
}

void	rb(t_stack *stack_b)
{
	if (!stack_b || stack_b->size < 2)
		return ;
	rotate_stack(stack_b);
	write(1, "rb\n", 3);
}

void	rr(t_stack *stack_a, t_stack *stack_b)
{
	bool	rotated_a;
	bool	rotated_b;

	rotated_a = (stack_a && stack_a->size >= 2);
	rotated_b = (stack_b && stack_b->size >= 2);
	if (!rotated_a && !rotated_b)
		return ;
	if (rotated_a)
		rotate_stack(stack_a);
	if (rotated_b)
		rotate_stack(stack_b);
	write(1, "rr\n", 3);
}
