/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   small_sort.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erazumov <erazumov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 12:51:07 by erazumov          #+#    #+#             */
/*   Updated: 2025/04/12 17:52:53 by erazumov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	sort_three(t_stack *a)
{
	int	top;
	int	mid;
	int	bot;

	top = a->head->value;
	mid = a->head->next->value;
	bot = a->tail->value;
	if (top > mid && mid < bot && top < bot)
		sa(a);
	else if (top > mid && mid > bot)
	{
		sa(a);
		rra(a);
	}
	else if (top > mid && mid < bot && top > bot)
		ra(a);
	else if (top < mid && mid > bot && top < bot)
	{
		sa(a);
		ra(a);
	}
	else if (top < mid && mid > bot && top > bot)
		rra(a);
}

void	sort_four(t_stack *a, t_stack *b)
{
	int		min_pos;
	t_node	*current;

	min_pos = 0;
	current = a->head;
	while (current && current->value != find_min(a))
	{
		min_pos++;
		current = current->next;
	}
	if (min_pos <= a->size / 2)
	{
		while (a->head->value != find_min(a))
			ra(a);
	}
	else
	{
		while (a->head->value != find_min(a))
			rra(a);
	}
	pb(a, b);
	sort_three(a);
	pa(a, b);
	if (a->head->value > a->head->next->value)
		sa(a);
}

void	sort_five(t_stack *a, t_stack *b)
{
	while (a->size > 3)
	{
		if (a->head->value == find_min(a)
				|| a->head->value == find_second_min(a))
			pb(a, b);
		else
			ra(a);
	}
	sort_three(a);
	while (b->size)
		pa(a, b);
}

void	small_sort(t_stack *a, t_stack *b)
{
	if (a->size == 2 && a->head->value > a->head->next->value)
		sa(a);
	else if (a->size == 3)
		sort_three(a);
	else if (a->size == 4)
		sort_four(a, b);
	else if (a->size == 5)
		sort_five(a, b);
}
