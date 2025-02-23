/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   if_sorted.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erazumov <erazumov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/23 11:18:00 by erazumov          #+#    #+#             */
/*   Updated: 2025/02/23 11:31:20 by erazumov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* Checks if the stack is already sorted to avoid unnecessary operations. */

# include "push_swap.h"

int	if_sorted(t_stack *stack)
{
	while (stack && stack->next)
	{
		if (stack->item > stack->next->item)
			return (0);
		stack = stack->next;
	}
	return (1);
}

int main(int ac, char **av)
{
	t_stack	*stack_a;
	t_stack	*stack_b;

	if (ac < 2)
		return (0);

	
}

