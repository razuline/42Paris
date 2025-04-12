/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   small_sort.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erazumov <erazumov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 12:51:07 by erazumov          #+#    #+#             */
/*   Updated: 2025/04/12 11:01:48 by erazumov         ###   ########.fr       */
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
	else if (top > mid && mid < bot)
		ra(a);
	else if (top < mid && mid > bot && top > bot)
	{
		sa(a);
		ra(a);
	}
	else if (top < mid && mid > bot && top > bot)
		rra(a);
}

void	small_sort(t_stack *a, t_stack *b)
{
	if (a->size == 2 && a->head->value > a->head->next->value)
		sa(a);
	else if (a->size == 3)
		sort_three(a);
	else if (a->size <= 5)
	{
		while (a->size > 3)
			pb(a, b);
		sort_three(a);
		while (b->size > 0)
			pa(a, b);
	}
}
