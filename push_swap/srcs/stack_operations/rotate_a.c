/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotate_a.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erazumov <erazumov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/25 17:38:13 by erazumov          #+#    #+#             */
/*   Updated: 2025/01/25 17:52:09 by erazumov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/push_swap.h"

void	rotate_a(t_stacks *stack_a)
{
	int	tmp;
	int	i;

	if (stack_a->size > 1) /* check if the num of elem is greater than 1*/
	{
		tmp = stack_a->arr[0]; /* Save the 1st element */
		i = 1;
		if (i < stack_a->size)
		{
			stack_a->arr[i - 1] = stack_a->arr[i]; /* move elements to the left */
			i++;
		}
	}
	stack_a->arr[stack_a->size - 1] = tmp; /* move the 1st element to end of A*/
	write(1, "rotate_a\n", 9);
}
