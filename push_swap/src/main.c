/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erazumov <erazumov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/13 13:31:30 by erazumov          #+#    #+#             */
/*   Updated: 2025/04/19 11:51:10 by erazumov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/push_swap.h"

void	push_swap(int ac, char **av)
{
	t_stack	*stack_a;
	t_stack	*stack_b;

	stack_a = init_stack();
	if (!stack_a)
		error_exit(stack_a, NULL);
	parse_fill_stack(ac, av, stack_a);
	stack_b = init_stack();
	if (!stack_b)
		error_exit(NULL, stack_b);
	if (is_sorted(stack_a))
		return (free_stacks(stack_a, stack_b));
	if (stack_a->size == 2)
		sort_two(stack_a);
	else if (stack_a->size == 3)
		sort_three(stack_a);
	else if (stack_a->size == 4)
		sort_four(stack_a, stack_b);
	else if (stack_a->size == 5)
		sort_five(stack_a, stack_b);
	else
		sort_large(stack_a, stack_b);
	free_stack(stack_a);
	free_stack(stack_b);
}

int	main(int ac, char **av)
{
	if (ac == 1)
		return (0);
	push_swap(ac, av);
	return (0);
}
