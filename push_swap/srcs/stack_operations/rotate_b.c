/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotate_b.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erazumov <erazumov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/25 17:51:13 by erazumov          #+#    #+#             */
/*   Updated: 2025/01/25 17:55:06 by erazumov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/push_swap.h"

void	rotate_b(t_stacks *stack_b)
{
	int	tmp;
	int	i;

	if (stack_b->size > 1)
	{
		tmp = stack_b->arr[0];
		i = 1;
		if (i < stack_b->size)
		{
			stack_b->arr[i - 1] = stack_b->arr[i];
			i++;
		}
	}
	stack_b->arr[stack_b->size - 1] = tmp;
	write(1, "rotate_b\n", 9);
}
