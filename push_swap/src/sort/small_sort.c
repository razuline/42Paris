/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   small_sort.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erazumov <erazumov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 12:51:07 by erazumov          #+#    #+#             */
/*   Updated: 2025/04/09 13:44:50 by erazumov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../includes/push_swap.h"

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

static void	push_min_to_b(t_stack *a, t_stack *b)
{
	t_node	*min_node;

	min_node = a->head;
	while (min_node->value != find_min(a))
	{
		ra(a);
		min_node = a->head;
	}
	pb(a, b);
}

void	sort_five(t_stack *a, t_stack *b)
{
	int	original_size;

	original_size = a->size;
	while (a->size > 3)
		push_min_to_b(a, b);
	sort_three(a);
	while (b->size > 0)
		pa(a, b);
	if (original_size == 5)
	{
		if (a->head->value > a->head->next->value)
			sa(a);
	}
}

void	sort_small(t_stack *a, t_stack *b)
{
	if (a->size == 2)
		sa(a);
	else if (a->size == 3)
		sort_three(a);
	else if (a->size <= 5)
		sort_five(a, b);
}
