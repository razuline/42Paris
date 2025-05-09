/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_large.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erazumov <erazumov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/13 14:18:38 by erazumov          #+#    #+#             */
/*   Updated: 2025/04/19 12:01:05 by erazumov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/push_swap.h"

static void	process_one_chunk(t_stack *a, t_stack *b, int elems_to_push,
				int max_idx);
static void	push_chunks_to_b(t_stack *a, t_stack *b, t_chunk_info *info);
static void	push_sorted_to_a(t_stack *a, t_stack *b, t_chunk_info *info);

void	sort_large(t_stack *stack_a, t_stack *stack_b)
{
	t_chunk_info	info;

	info.total_size = stack_a->size;
	if (info.total_size <= 5)
		return ;
	assign_index(stack_a);
	if (info.total_size <= 100)
		info.num_chunks = 5;
	else
		info.num_chunks = 11;
	info.chunk_size = info.total_size / info.num_chunks;
	push_chunks_to_b(stack_a, stack_b, &info);
	push_sorted_to_a(stack_a, stack_b, &info);
}

static void	process_one_chunk(t_stack *a, t_stack *b, int elems_to_push,
			int max_idx)
{
	int		pushed_count;
	t_node	*node_to_push;

	pushed_count = 0;
	while (pushed_count < elems_to_push && a->size > 0)
	{
		node_to_push = find_cheapest_node(a, max_idx);
		if (!node_to_push)
			break ;
		node_to_top_a(a, node_to_push);
		pb(a, b);
		pushed_count++;
	}
}

static void	push_chunks_to_b(t_stack *a, t_stack *b, t_chunk_info *info)
{
	int	curr_chunk;
	int	max_idx_in_chunk;
	int	elems_in_chunk;

	curr_chunk = 0;
	while (curr_chunk < info->num_chunks)
	{
		max_idx_in_chunk = (curr_chunk + 1) * info->chunk_size - 1;
		if (curr_chunk == info->num_chunks - 1)
			max_idx_in_chunk = info->total_size - 1;
		elems_in_chunk = info->chunk_size;
		if (curr_chunk == info->num_chunks - 1)
			elems_in_chunk = info->total_size - (curr_chunk * info->chunk_size);
		process_one_chunk(a, b, elems_in_chunk, max_idx_in_chunk);
		curr_chunk++;
	}
	while (a->size > 0)
		pb(a, b);
}

static void	push_sorted_to_a(t_stack *a, t_stack *b, t_chunk_info *info)
{
	int		target_idx;
	t_node	*node_to_move;

	target_idx = info->total_size - 1;
	while (b->size > 0)
	{
		node_to_move = find_node_by_idx(b, target_idx);
		if (!node_to_move)
			error_exit(a, b);
		node_to_top_b(b, node_to_move);
		pa(a, b);
		target_idx--;
	}
}
