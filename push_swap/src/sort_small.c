/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_small.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erazumov <erazumov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 12:51:07 by erazumov          #+#    #+#             */
/*   Updated: 2025/04/09 12:28:36 by erazumov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../includes/push_swap.h"

t_node	*find_min(t_stack *stack)
{
	t_node	*min;
	t_node	*current;

	if (!stack || !stack->head)
		return (NULL);
	min = stack->head;
	current = stack->head->next;
	while (current)
	{
		if (current->value < min->value)
			min = current;
		current = current->next;
	}
	return (min);
}
void	sort_three(t_stack *a)
{
	int	top;
	int	mid;
	int	bot;

	top = a->head->value;
	mid = a->head->next->value;
	bot = a->tail->value;
	if (top > mid && mid < bot && top < bot)
		swap(a);
	else if (top > mid && mid > bot)
	{
		swap(a);
		rra(a);
	}
	else if (top > mid && mid < bot && top > bot)
		ra(a);
	else if (top < mid && mid > bot && top < bot)
	{
		swap(a);
		ra(a);
	}
	else if (top < mid && mid > bot && top > bot)
		rra(a);
}

void	sort_small(t_stack *a, t_stack *b)
{
	t_node	*min;

	if (a->size == 2)
		sa(a);
	else if (a->size == 3)
		sort_three(a);
	else
	{
		while (a->size > 3)
		{
			min = find_min(a);
			while (a->head != min)
			{
				if (min == a->tail)
					rra(a);
				else
					ra(a);
			}
			pb(a, b);
		}
		sort_three(a);
		while (b->size > 0)
			pa(a, b);
	}
}
