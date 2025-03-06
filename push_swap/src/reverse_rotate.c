/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reverse_rotate.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erazumov <erazumov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/23 15:38:09 by erazumov          #+#    #+#             */
/*   Updated: 2025/03/06 13:21:16 by erazumov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "push_swap.h"

void	reverse_rotate(t_stack **stack)
{
	t_stack *last;
	t_stack *second_last;
	
	if (*stack && (*stack)->next)
	{
		last = *stack;
		while (last->next)
			last = last->next;
		second_last = NULL;
		while (second_last->next != last)
			second_last = second_last->next;
		second_last->next = NULL;
		last->next = *stack;
		*stack = last;
	}
}
/*
void	rra(t_stack **a)
{
	reverse_rotate(a);
	ft_printf("rra\n");
}

void	rrb(t_stack **b)
{
	reverse_rotate(b);
	ft_printf("rrb\n");
}

void	rrr(t_stack **a, t_stack **b)
{
	reverse_rotate(a);
	reverse_rotate(b);
	ft_printf("rrr\n");
}
*/