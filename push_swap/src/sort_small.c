/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_small.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erazumov <erazumov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/13 13:50:38 by erazumov          #+#    #+#             */
/*   Updated: 2025/04/13 19:46:08 by erazumov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/push_swap.h"

static t_node	*find_min_node(t_stack *stack)
{
	t_node	*min_node;
	t_node	*current;

	if (!stack || !stack->head)
		return (NULL);
	min_node = stack->head;
	current = stack->head->next;
	while (current)
	{
		if (current->value < min_node->value)
			min_node = current;
		current = current->next;
	}
	return (min_node);
}

void	sort_two(t_stack *stack_a)
{
	if (stack_a->head->value > stack_a->head->next->value)
		sa(stack_a);
}

void	sort_three(t_stack *stack_a)
{
	t_node	*head_sort;
	t_node	*mid_sort;
	t_node	*tail_sort;
	int		max_val;

	head_sort = stack_a->head;
	mid_sort = head_sort->next;
	tail_sort = stack_a->tail;
	max_val = head_sort->value;
	if (mid_sort->value > max_val)
		max_val = mid_sort->value;
	if (tail_sort->value > max_val)
		max_val = tail_sort->value;
	if (head_sort->value == max_val)
		ra(stack_a);
	else if (mid_sort->value == max_val)
		rra(stack_a);
	if (stack_a->head->value > stack_a->head->next->value)
		sa(stack_a);
}

void	sort_four(t_stack *stack_a, t_stack *stack_b)
{
	t_node	*min_node;

	min_node = find_min_node(stack_a);
	node_to_top_a(stack_a, min_node);
	pb(stack_a, stack_b);
	sort_three(stack_a);
	pa(stack_a, stack_b);
}

void	sort_five(t_stack *stack_a, t_stack *stack_b)
{
	t_node	*min_node;

	min_node = find_min_node(stack_a);
	node_to_top_a(stack_a, min_node);
	pb(stack_a, stack_b);

	min_node = find_min_node(stack_a);
	node_to_top_a(stack_a, min_node);
	pb(stack_a, stack_b);
	sort_three(stack_a);
	pa(stack_a, stack_b);
	pa(stack_a, stack_b);
}
