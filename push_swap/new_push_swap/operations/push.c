/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erazumov <erazumov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 14:35:03 by erazumov          #+#    #+#             */
/*   Updated: 2025/03/07 15:17:59 by erazumov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../push_swap.h"

static void	init_ptr(t_elem **stack, t_elem **ls, t_elem **nd, t_elem **snd)
{
	ls = (*stack)->prev;
	nd = *stack;
	snd = (*stack)->next;
	ft_printf("pa\n");
}

void	pa(t_elem **stack_a, t_elem **stack_b)
{
	int			a;
	t_elem	*node;
	t_elem	*second;
	t_elem	*last;

	if (!(*stack_b))
		return ;
	a = 1;
	if ((*stack_b)->next == *stack_b && (*stack_b)->prev == *stack_b)
		a = 0;
	init_ptr(stack_b, &last, &node, &second);
	node->next = *stack_a;
	(*stack_a)->prev->next = node;
	node->prev = (*stack_a)->prev;
	(*stack_a)->prev = node;
	*stack_a = node;
	if (!a)
		*stack_b = NULL;
	else
	{
		*stack_b = second;
		(*stack_b)->prev = last;
		last->next = *stack_b;
	}
}

void	pb(t_elem **stack_a, t_elem **stack_b)
{
	t_elem	*node;

	if (!(*stack_a))
		return ;
	node = *stack_a;
	*stack_a = (*stack_a)->next;
	(*stack_a)->prev = node->prev;
	(*stack_a)->prev->next = *stack_a;
	if (!(*stack_b))
	{
		node->prev = node;
		node->next = node;
		*stack_b = node;
	}
	else
	{
		node->next = *stack_b;
		node->prev = (*stack_b)->prev;
		*stack_b = node;
		(*stack_b)->prev->next = *stack_b;
		(*stack_b)->next->prev = *stack_b;
	}
	ft_printf("pb\n");
}
