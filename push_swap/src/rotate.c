/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotate.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erazumov <erazumov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/23 15:37:54 by erazumov          #+#    #+#             */
/*   Updated: 2025/03/06 13:17:30 by erazumov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "push_swap.h"

void	rotate(t_stack **stack)
{
	t_stack *first;
	t_stack *last;
	
	if (*stack && (*stack)->next)
	{
		first = *stack;
		*stack = first->next;
		last = *stack;
		while (last->next)
			last = last->next;
		last->next = first;
		first->next = NULL;
	}
}
/*
void	ra(t_stack **a)
{
	rotate(a);
	ft_printf("ra\n");
}

void	rb(t_stack **b)
{
	rotate(b);
	ft_printf("rb\n");
}

void	rr(t_stack **a, t_stack **b)
{
	rotate(a);
	rotate(b);
	ft_printf("rr\n");
}
*/