/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rev_rotate.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erazumov <erazumov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/13 13:46:39 by erazumov          #+#    #+#             */
/*   Updated: 2025/04/13 14:38:13 by erazumov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/push_swap.h"

static void	reverse_rotate_stack(t_stack *stack)
{
	t_node	*last;
	t_node	*second_last;

	if (!stack || stack->size < 2)
		return ;
	last = stack->tail;
	second_last = last->prev;
	second_last->next = NULL;
	stack->head->prev = last;
	last->next = stack->head;
	last->prev = NULL;
	stack->head = last;
	stack->tail = second_last;
}

void	rra(t_stack *stack_a)
{
	if (!stack_a || stack_a->size < 2)
		return ;
	reverse_rotate_stack(stack_a);
	write(1, "rra\n", 4);
}

void	rrb(t_stack *stack_b)
{
	if (!stack_b || stack_b->size < 2)
		return ;
	reverse_rotate_stack(stack_b);
	write(1, "rrb\n", 4);
}

void	rrr(t_stack *stack_a, t_stack *stack_b)
{
	bool	rev_rotated_a;
	bool	rev_rotated_b;

	rev_rotated_a = (stack_a && stack_a->size >= 2);
	rev_rotated_b = (stack_b && stack_b->size >= 2);
	if (!rev_rotated_a && !rev_rotated_b)
		return ;
	if (rev_rotated_a)
		reverse_rotate_stack(stack_a);
	if (rev_rotated_b)
		reverse_rotate_stack(stack_b);
	write(1, "rrr\n", 4);
}
