/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   swap.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erazumov <erazumov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/23 15:37:29 by erazumov          #+#    #+#             */
/*   Updated: 2025/03/05 10:42:02 by erazumov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "push_swap.h"

/* Swap the top two elements of a stack */
void	swap(t_stack **stack)
{
	if (!stack || !*stack || !(*stack)->next)
		return ;
	t_stack	*first = *stack;
	t_stack	*second = first->next;

	first->next = second->next;
	second->next = first;
	*stack = second;
}

void	sa(t_stack **a)
{
	swap(a);
	ft_printf("sa\n");
}

void	sb(t_stack **b)
{
	swap(b);
	ft_printf("sb\n");
}

void	ss(t_stack **a, t_stack **b)
{
	swap(a);
	swap(b);
	ft_printf("ss\n");
}
