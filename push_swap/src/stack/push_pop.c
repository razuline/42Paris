/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_pop.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erazumov <erazumov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 13:18:14 by erazumov          #+#    #+#             */
/*   Updated: 2025/04/09 17:51:24 by erazumov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	push_to(t_stack *stack, int value)
{
	t_node	*new;

	new = new_node(value);
	if (!stack->tail)
		stack->head = new;
	else
	{
		stack->tail->next = new;
		new->prev = stack->tail;
	}
	stack->tail = new;
	stack->size++;
}

int	pop(t_stack *stack)
{
	int		value;
	t_node	*tmp;

	if (!stack->head)
		if_error("Error: Stack is empty!\n");
	tmp = stack->head;
	value = tmp->value;
	stack->head = tmp->next;
	if (stack->head)
		stack->head->prev = NULL;
	else
		stack->tail = NULL;
	free(tmp);
	stack->size--;
	return (value);
}
