/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erazumov <erazumov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 16:48:00 by erazumov          #+#    #+#             */
/*   Updated: 2025/04/21 16:50:24 by erazumov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	init_stack(t_stack *stack)
{
	stack->top = -1;
}

int	push(t_stack *stack, t_point p)
{
	if (stack->top >= MAX_STACK_SIZE - 1)
	{
		ft_putstr_fd("Error\nFlood fill stack overflow! "
			"Increase MAX_STACK_SIZE.\n", 2);
		return (0);
	}
	stack->top++;
	stack->coords[stack->top] = p;
	return (1);
}

t_point	pop(t_stack *stack)
{
	if (stack->top < 0)
		return ((t_point){-1, -1});
	return (stack->coords[stack->top--]);
}
