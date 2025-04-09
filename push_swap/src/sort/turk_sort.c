/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   turk_sort.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erazumov <erazumov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/09 09:03:18 by erazumov          #+#    #+#             */
/*   Updated: 2025/04/09 16:37:09 by erazumov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/push_swap.h"

static int	get_median(t_stack *stack)
{
	t_node	*current;
	int		*arr;
	int		i;
	int		median;

	arr = (int *)malloc(sizeof(int) * stack->size);
	if (!arr)
		if_error("Error: Memory allocation failed!\n");
	current = stack->head;
	i = 0;
	while (current)
	{
		arr[i++] = current->value;
		current = current->next;
	}
	ft_sort_int_tab(arr, stack->size);
	median = arr[stack->size / 2];
	free(arr);
	return (median);
}

static int	get_chunk_size(t_stack *stack)
{
	int	size;

	size = stack->size;
	if (size <= 100)
		return (15);
	else
		return (30);
}

static void	push_chunks_to_b(t_stack *a, t_stack *b)
{
	int	chunk_size;
	int	pushed;
	int	median;

	chunk_size = get_chunk_size(a);
	while (a->size > 3)
	{
		median = get_median(a);
		pushed = 0;
		while (pushed < chunk_size && a->size > 3)
		{
			if (a->head->value < median)
			{
				pb(a, b);
				pushed++;
			}
			else
				ra(a);
		}
	}
}

static void	push_back_to_a(t_stack *a, t_stack *b)
{
	int	target_pos;

	while (b->size > 0)
	{
		target_pos = find_target_position(a, b->head->value);
		move_to_position(a, target_pos, 1);
		pa(a, b);
	}
}

void	turk_sort(t_stack *a, t_stack *b)
{
	push_chunks_to_b(a, b);
	sort_three(a);
	push_back_to_a(a, b);
	final_rotate(a);
}
