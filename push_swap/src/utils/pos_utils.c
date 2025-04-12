/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pos_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erazumov <erazumov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/12 17:51:37 by erazumov          #+#    #+#             */
/*   Updated: 2025/04/12 18:09:54 by erazumov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static int	calculate_move_score(t_stack *a, t_stack *b, int pos)
{
	int	target_pos;
	int	move_a;
	int	move_b;
	int	total;

	target_pos = find_target_pos(a, b->head->value);
	if (pos <= b->size / 2)
		move_b = pos;
	else
		move_b = b->size - pos;
	if (target_pos <= a->size / 2)
		move_a = target_pos;
	else
		move_a = a->size - target_pos;
	total = move_a + move_b;
	if ((pos <= b->size / 2 && target_pos <= a->size / 2)
			|| (pos > b->size / 2 && target_pos > a->size / 2))
	{
		if (move_a > move_b)
			total -= move_b;
		else
			total -= move_a;
	}
	return (total);
}

static void	rotate_stack(t_stack *s, int direction, int *count)
{
	if (direction)
	{
		ra(s);
		(*count)--;
	}
	else
	{
		rra(s);
		(*count)++;
	}
}

static void	execute_best_move(t_stack *a, t_stack *b, int pos)
{
	int	target_pos;
	int	rotate_a;
	int	rotate_b;

	target_pos = find_target_pos(a, b->head->value);
	rotate_a = (target_pos <= a->size / 2);
	rotate_b = (pos <= b->size / 2);
	while ((rotate_a && target_pos > 0) || (!rotate_a && target_pos < a->size))
		rotate_stack(a, rotate_a, &target_pos);
	while ((rotate_b && pos > 0) || (!rotate_b && pos < b->size))
		rotate_stack(b, rotate_b, &pos);
	pa(a, b);
}

void	find_best_move(t_stack *a, t_stack *b)
{
	t_node	*current;
	int		best_score;
	int		current_score;
	int		best_pos;
	int		pos;

	current = b->head;
	best_score = INT_MAX;
	pos = 0;
	while (current)
	{
		current_score = calculate_move_score(a, b, pos);
		if (current_score < best_score)
		{
			best_score = current_score;
			best_pos = pos;
		}
		current = current->next;
		pos++;
	}
	execute_best_move(a, b, best_pos);
}
