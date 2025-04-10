/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erazumov <erazumov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 14:05:04 by erazumov          #+#    #+#             */
/*   Updated: 2025/04/09 17:19:09 by erazumov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/push_swap.h"

void	ft_sort_int_tab(int *tab, int size)
{
	int	i;
	int	j;
	int	tmp;

	i = 0;
	while (i < size - 1)
	{
		j = i + 1;
		while (j < size)
		{
			if (tab[i] > tab[j])
			{
				tmp = tab[i];
				tab[i] = tab[j];
				tab[j] = tmp;
			}
			j++;
		}
		i++;
	}
}

void	final_rotate(t_stack *a)
{
	int	min_pos;
	int	min;

	min = find_min(a);
	min_pos = find_position(a, min);
	if (min_pos <= a->size / 2)
	{
		while (a->head->value != min)
			ra(a);
	}
	else
	{
		while (a->head->value != min)
			rra(a);
	}
}

void	move_to_position(t_stack *stack, int pos, int direction)
{
	int	i;

	i = 0;
	while (i < pos)
	{
		if (direction)
			ra(stack);
		else
			rra(stack);
		i++;
	}
}

int	find_min_position(t_stack *stack)
{
	t_node	*current = stack->head;
	int	min = current->value;
	int	pos = 0;
	int	min_pos = 0;

	while (current)
	{
		if (current->value < min)
		{
			min = current->value;
			min_pos = pos;
		}
		current = current->next;
		pos++;
	}
	return (min_pos);
}
