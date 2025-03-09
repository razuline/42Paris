/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_small.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erazumov <erazumov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 12:51:07 by erazumov          #+#    #+#             */
/*   Updated: 2025/03/09 09:18:11 by erazumov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../push_swap.h"

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
	int	first;
	int	second;
	int	third;

	first = a->head->value;
	second = a->head->next->value;
	third = a->tail->value;
	if (first > second && second < third && first < third)
		sa(a);
	else if (first > second && second > third)
	{
		sa(a);
		ra(a);
	}
	else if (first < second && second > third && first > third)
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
