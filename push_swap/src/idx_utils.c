/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   idx_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erazumov <erazumov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/13 14:06:56 by erazumov          #+#    #+#             */
/*   Updated: 2025/04/13 14:37:50 by erazumov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/push_swap.h"

static void	swap_arr_values(int *a, int *b)
{
	int	tmp;

	tmp = *a;
	*a = *b;
	*b = tmp;
}

static void	bubble_sort_array(int *arr, int size)
{
	int		i;
	int		j;
	bool	swapped;

	if (!arr || size < 2)
		return ;
	i = 0;
	while (i < size - 1)
	{
		swapped = false;
		j = 0;
		while (j < size - i - 1)
		{
			if (arr[j] > arr[j + 1])
			{
				swap_arr_values(&arr[j], &arr[j + 1]);
				swapped = true;
			}
			j++;
		}
		if (!swapped)
			break ;
		i++;
	}
}

static void	fill_arr_from_stack(t_stack *stack, int *arr)
{
	int		i;
	t_node	*current;

	current = stack->head;
	i = 0;
	while (current)
	{
		arr[i] = current->value;
		current->index = -1;
		i++;
		current = current->next;
	}
}

static void	set_idx_from_arr(t_stack *stack, int *sorted_arr)
{
	int		i;
	int		size;
	t_node	*current;

	size = stack->size;
	current = stack->head;
	while (current)
	{
		i = 0;
		while (i < size)
		{
			if (current->value == sorted_arr[i])
			{
				current->index = i;
				break ;
			}
			i++;
		}
		current = current->next;
	}
}

void	assign_index(t_stack *stack_a)
{
	int	*tmp_arr;
	int	stack_size;

	if (!stack_a || stack_a->size < 2)
	{
		if (stack_a && stack_a->size == 1)
			stack_a->head->index = 0;
		return ;
	}
	stack_size = stack_a->size;
	tmp_arr = (int *)malloc(sizeof(int) * stack_size);
	if (!tmp_arr)
		error_exit(stack_a, NULL);
	fill_arr_from_stack(stack_a, tmp_arr);
	bubble_sort_array(tmp_arr, stack_size);
	set_idx_from_arr(stack_a, tmp_arr);
	free(tmp_arr);
}
