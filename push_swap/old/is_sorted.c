/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_sorted.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erazumov <erazumov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/23 11:18:00 by erazumov          #+#    #+#             */
/*   Updated: 2025/03/06 11:46:06 by erazumov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* Checks if the stack is already sorted to avoid unnecessary operations. */

# include "push_swap.h"

int	is_sorted(t_stack *stack)
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
	stack_a = sort_input(ac, av);
	if (!stack_a)
	{
		ft_printf("Error!\n");
		return (1);
	}
	if (is_sorted(stack_a))
	{
		free_if_error(&stack_a);
		return (0);
	}
	// Choose sorting algorithm based on stack size
	if (stack_size(stack_a) == 2)
		sort_2(&stack_a);
	else if (stack_size(stack_a) == 3)
		sort_3(&stack_a);
	else if (stack_size(stack_a) <= 5)
		sort_5(&stack_a, &stack_b);
	else
		sort_large(&stack_a, &stack_b);

	// Free memory before exiting
	free_stack(&stack_a);
	free_stack(&stack_b);
	return (0);
}
