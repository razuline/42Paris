/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erazumov <erazumov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 12:53:26 by erazumov          #+#    #+#             */
/*   Updated: 2025/03/06 13:10:16 by erazumov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "push_swap.h"

/* Remove an element from the stack */
int	pop(t_stack **stack)
{
	int		num;
	t_stack	*tmp;

	if (!stack)
		return (0);
	tmp = *stack;
	*stack = (*stack)->next;
	num = tmp->number;
	free(tmp);
	return (num);
}

int	stack_size(t_stack *stack)
{
	int	size;

	size = 0;
	while (stack)
	{
		size++;
		stack = stack->next;
	}
	return (size);
}

int	if_stack_empty(t_stack *stack)
{
	return (stack == NULL);
}
