/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erazumov <erazumov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/13 13:38:52 by erazumov          #+#    #+#             */
/*   Updated: 2025/04/13 13:41:25 by erazumov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/push_swap.h"

static void	push_stack(t_stack *dst, t_stack *src)
{
	t_node	*node_to_move;

	if (!src || src->size == 0)
		return ;
	node_to_move = src->head;
	src->head = node_to_move->next;
	if (src->head != NULL)
		src->head->prev = NULL;
	else
		src->tail = NULL;
	src->size--;
	node_to_move->prev = NULL;
	node_to_move->next = dst->head;
	if (dst->head != NULL)
		dst->head->prev = node_to_move;
	else
		dst->tail = node_to_move;
	dst->head = node_to_move;
	dst->size++;
}

void	pa(t_stack *stack_a, t_stack *stack_b)
{
	if (!stack_b || stack_b->size == 0)
		return ;
	push_stack(stack_a, stack_b);
	write(1, "pa\n", 3);
}

void	pb(t_stack *stack_a, t_stack *stack_b)
{
	if (!stack_a || stack_a->size == 0)
		return ;
	push_stack(stack_b, stack_a);
	write(1, "pb\n", 3);
}
