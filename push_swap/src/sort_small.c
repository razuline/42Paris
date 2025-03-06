/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_small.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erazumov <erazumov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 13:28:58 by erazumov          #+#    #+#             */
/*   Updated: 2025/03/06 13:35:46 by erazumov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "push_swap.h"

void	sort_two(t_stack **stack)
{
	if ((*stack)->number > (*stack)->next->number)
		swap(stack);
}

void	sort_three(t_stack **stack)
{
	if ((*stack)->number > (*stack)->next->number)
		swap(stack);
	if ((*stack)->number > (*stack)->next->next->number)
	{
		rotate(stack);
		swap(stack);
	}
	if ((*stack)->next->number > (*stack)->next->next->number)
		reverse_rotate(stack);
}

void	sort_five(t_stack **stack)
{
	if ((*stack)->number > (*stack)->next->number)
		swap(stack);
	rotate(stack);
	if ((*stack)->number > (*stack)->next->number)
		swap(stack);
	reverse_rotate(stack);
}
