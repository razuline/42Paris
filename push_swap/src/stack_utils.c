/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erazumov <erazumov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/13 12:47:14 by erazumov          #+#    #+#             */
/*   Updated: 2025/04/19 12:06:05 by erazumov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/push_swap.h"

t_stack	*init_stack(void)
{
	t_stack	*stack;

	stack = (t_stack *)malloc(sizeof(t_stack));
	if (!stack)
		return (NULL);
	stack->size = 0;
	stack->head = NULL;
	stack->tail = NULL;
	return (stack);
}

void	free_stack(t_stack *stack)
{
	t_node	*current;
	t_node	*next_node;

	if (!stack)
		return ;
	current = stack->head;
	while (current != NULL)
	{
		next_node = current->next;
		free(current);
		current = next_node;
	}
	free(stack);
}

void	free_stacks(t_stack *stack_a, t_stack *stack_b)
{
	if (stack_a)
		free_stack(stack_a);
	if (stack_b)
		free_stack(stack_b);
}

void	add_node_front(t_stack *stack, t_node *new_node)
{
	if (!stack || !new_node)
		return ;
	if (stack->size == 0)
	{
		stack->head = new_node;
		stack->tail = new_node;
		new_node->prev = NULL;
		new_node->next = NULL;
	}
	else
	{
		new_node->prev = NULL;
		new_node->next = stack->head;
		stack->head->prev = new_node;
		stack->head = new_node;
	}
	stack->size++;
}

void	add_node_back(t_stack *stack, t_node *new_node)
{
	if (!stack || !new_node)
		return ;
	if (stack->size == 0)
	{
		stack->head = new_node;
		stack->tail = new_node;
		new_node->prev = NULL;
		new_node->next = NULL;
	}
	else
	{
		new_node->prev = stack->tail;
		new_node->next = NULL;
		stack->tail->next = new_node;
		stack->tail = new_node;
	}
	stack->size++;
}
