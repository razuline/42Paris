/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   swap_a.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erazumov <erazumov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 13:42:05 by erazumov          #+#    #+#             */
/*   Updated: 2025/01/29 18:47:11 by erazumov         ###   ########.fr       */
/*   Updated: 2025/01/25 17:39:01 by erazumov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/push_swap.h"

void	swap_a(t_stacks *stack_a)
{
	int	tmp;

	if (stack_a->size >= 2)
	{
		tmp = stack_a->arr[0]; /* var tmp for the 1st element */
		stack_a->arr[0] = stack_a->arr[1]; /* 2nd element becomes the 1st */
		stack_a->arr[1] = tmp; /* 1st element becomes the 2nd */
		write(1, "swap_a\n", 7);
	}
}
