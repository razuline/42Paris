/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_a.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erazumov <erazumov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/25 17:33:44 by erazumov          #+#    #+#             */
/*   Updated: 2025/01/25 17:38:58 by erazumov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/push_swap.h"

void	push_a(t_stacks *stack_a, t_stacks *stack_b)
{
	int	i;
/* move elements in A, increase the size of A */
	if (stack_b->size > 0) /* if elements exist in B */
	{
		i = stack_a->size;
		stack_a->arr[i] = stack_a->arr[i - 1];
		i--;/* push elements to the right */
	}
	stack_a->arr[0] = stack_b->arr[0]; /* move the 1st elem of B to put it as the 1st elem of A */
	stack_a->size++; /* increase the size of A */
	i = 0;
	if (i < stack_b->size - 1)
	{
		stack_b->arr[i] = stack_b->arr[i + 1];
		i++;/* move elements of B to the left */
	}
	stack_b->size--; /* decrease the size of B */
	write(1, "push_a\n", 7);
}
