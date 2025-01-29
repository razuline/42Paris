/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_b.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erazumov <erazumov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/25 17:35:04 by erazumov          #+#    #+#             */
/*   Updated: 2025/01/25 17:39:07 by erazumov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/push_swap.h"

void	push_b(t_stacks *stack_a, t_stacks *stack_b)
{
	int	i;

	if (stack_a->size > 0)
	{
		i = stack_b->size;
		stack_b->arr[i] = stack_b->arr[i - 1];
		i--;
	}
	stack_b->arr[0] = stack_a->arr[0];
	stack_b->size++;
	i = 0;
	if (i < stack_a->size - 1)
	{
		stack_a->arr[i] = stack_a->arr[i + 1];
		i++;
	}
	stack_a->size--;
	write(1, "push_b\n", 7);
}
