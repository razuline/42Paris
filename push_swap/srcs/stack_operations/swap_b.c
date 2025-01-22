/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   swap_b.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erazumov <erazumov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 13:46:58 by erazumov          #+#    #+#             */
/*   Updated: 2025/01/22 13:53:02 by erazumov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/push_swap.h"

void	swap_b(t_stacks *stack_b)
{
	int	tmp;

	if (stack_b->size >= 2)
	{
		tmp = stack_b->arr[0]; /* var tmp for the 1st element */
		stack_b->arr[0] = stack_b->arr[1]; /* 2nd element becomes the 1st */
		stack_b->arr[1] = temp; /* 1st element becomes the 2nd */
		write(1, "swap_b\n", 7);
	}
}
