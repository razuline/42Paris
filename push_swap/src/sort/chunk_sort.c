/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   chunk_sort.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erazumov <erazumov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/12 11:02:33 by erazumov          #+#    #+#             */
/*   Updated: 2025/04/12 11:13:59 by erazumov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static void	push_chunk(t_stack *a, t_stack *b, int *chunk_size)
{
	int	pushed;

	pushed = 0;
	while (pushed++ < *chunk_size && a->size > 3)
	{
		if (a->head->value <= *chunk_size)
			pb(a, b);
		else
			ra(a);
	}
	*chunk_size += a->size / 5 + 1;
}

static void	return_to_a(t_stack *a, t_stack *b)
{
	int	target_pos;

	while (b->size)
	{
		target_pos = find_target_pos(a, b->head->value);
		if (target_pos > a->size / 2)
			while (target_pos++ < a->size)
				rra(a);
		else
			while (target_pos--)
				ra(a);
		pa(a, b);
	}
}

void	chunk_sort(t_stack *a, t_stack *b)
{
	int	chunk_size;

	chunk_size = a->size / 5 + 1;
	while (a->size > 3)
		push_chunk(a, b, &chunk_size);
	sort_three(a);
	return_to_a(a, b);
	final_rotate(a);
}
