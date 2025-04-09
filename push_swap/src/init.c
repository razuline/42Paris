/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erazumov <erazumov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 17:46:34 by erazumov          #+#    #+#             */
/*   Updated: 2025/04/09 12:53:48 by erazumov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../includes/push_swap.h"

/* Create an empty stack */
t_stack	*init_stack(void)
{
	t_stack	*stack;

	stack = (t_stack *)malloc(sizeof(t_stack));
	if (!stack)
		if_error("Error: Memory allocation failed!\n");
	stack->head = NULL;
	stack->tail = NULL;
	stack->size = 0;
	return (stack);
}

/* Free memory of a stack */
void	free_stack(t_stack *stack)
{
	t_node	*current;
	t_node	*tmp;

	if (!stack)
		return ;
	current = stack->head;
	while (current)
	{
		tmp = current->next;
		free(current);
		current = tmp;
	}
	free(stack);
}

/* Add a new element at the end of a stack */
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

/* Delete and return the last element of the stack */
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
