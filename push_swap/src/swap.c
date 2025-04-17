/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   swap.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erazumov <erazumov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/13 13:35:33 by erazumov          #+#    #+#             */
/*   Updated: 2025/04/13 13:37:47 by erazumov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/push_swap.h"

static void	swap_stack(t_stack *stack)
{
	t_node	*first;
	t_node	*second;

	if (!stack || stack->size < 2)
		return ;
	first = stack->head;
	second = first->next;
	first->next = second->next;
	if (second->next != NULL)
		second->next->prev = first;
	else
		stack->tail = first;
	second->prev = NULL;
	second->next = first;
	first->prev = second;
	stack->head = second;
}

void	sa(t_stack *stack_a)
{
	if (!stack_a || stack_a->size < 2)
		return ;
	swap_stack(stack_a);
	write(1, "sa\n", 3);
}

void	sb(t_stack *stack_b)
{
	if (!stack_b || stack_b->size < 2)
		return ;
	swap_stack(stack_b);
	write(1, "sb\n", 3);
}

void	ss(t_stack *stack_a, t_stack *stack_b)
{
	bool	swapped_a;
	bool	swapped_b;

	swapped_a = (stack_a && stack_a->size >= 2);
	swapped_b = (stack_b && stack_b->size >= 2);
	if (!swapped_a && !swapped_b)
		return ;
	if (swapped_a)
		swap_stack(stack_a);
	if (swapped_b)
		swap_stack(stack_b);
	write(1, "ss\n", 3);
}
