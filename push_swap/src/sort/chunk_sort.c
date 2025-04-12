/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   chunk_sort.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erazumov <erazumov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/12 11:02:33 by erazumov          #+#    #+#             */
/*   Updated: 2025/04/12 18:10:41 by erazumov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static int	calculate_distance(t_stack *a, int pos)
{
	if (pos <= a->size / 2)
		return (pos);
	else
		return (a->size - pos);
}

static bool	is_in_chunk(int value, int chunk_start, int chunk_end)
{
	return (value >= chunk_start && value <= chunk_end);
}

static int	find_next_chunk(t_stack *a, int c_start, int c_end)
{
	t_node	*cur;
	int		dist;
	int		pos;
	int		best[2] = {-1, INT_MAX};

	cur = a->head;
	pos = 0;
	while (cur && best[1] != 0)
	{
		if (cur->value >= c_start && cur->value <= c_end)
		{
			dist = (pos <= a->size / 2);
			if (dist)
				dist = pos;
			dist = a->size - pos;
			if (dist < best[1])
			{
				best[0] = pos;
				best[1] = dist;
			}
		}
		cur = cur->next;
		pos++;
	}
	return (best[0]);
}

static void	push_chunk(t_stack *a, t_stack *b, int chunk_start, int chunk_end)
{
	int	pos;

	while (1)
	{
		pos = find_next_chunk(a, chunk_start, chunk_end);
		if (pos == -1)
			break ;
		if (pos <= a->size / 2)
			while (pos-- > 0)
				ra(a);
		else
			while (pos++ < a->size)
				rra(a);
		pb(a, b);
	}
}

void	chunk_sort(t_stack *a, t_stack *b)
{
	int	chunk_size;
	int	num_chunks;
	int	i;

	chunk_size = a->size / 5 + (a->size % 5 != 0);
	num_chunks = 5;
	i = 0;
	while (i < num_chunks)
	{
		push_chunk(a, b, i * chunk_size, (i + 1) * chunk_size);
		i++;
	}
	sort_three(a);
	while (b->size)
	{
		find_best_move(a, b);
		pa(a, b);
	}
	final_rotate(a);
}
