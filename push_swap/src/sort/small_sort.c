/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   small_sort.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erazumov <erazumov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 12:51:07 by erazumov          #+#    #+#             */
/*   Updated: 2025/04/09 17:18:03 by erazumov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/push_swap.h"

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

static void	push_smallest_to_b(t_stack *a, t_stack *b)
{
	int	min_pos;
	int	size;

	min_pos = find_min_position(a);
	size = a->size;
	if (min_pos <= size / 2)
	{
		while (min_pos-- > 0)
			ra(a);
	}
	else
	{
		while (min_pos++ < size)
			rra(a);
	}
	pb(a, b);
}

void	sort_five(t_stack *a, t_stack *b)
{
	push_smallest_to_b(a, b);
	push_smallest_to_b(a, b);
	sort_three(a);
	pa(a, b);
	pa(a, b);
}

void	sort_small(t_stack *a, t_stack *b)
{
	if (a->size == 2 && a->head->value > a->head->next->value)
		sa(a);
	else if (a->size == 3)
		sort_three(a);
	else if (a->size <= 5)
		sort_five(a, b);
}
