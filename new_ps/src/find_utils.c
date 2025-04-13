/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erazumov <erazumov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/13 17:11:31 by erazumov          #+#    #+#             */
/*   Updated: 2025/04/13 18:00:30 by erazumov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/push_swap.h"

bool	is_sorted(t_stack *stack)
{
	t_node	*current;

	if (!stack || stack->size < 2)
		return (true);
	current = stack->head;
	while (current && current->next)
	{
		if (current->value > current->next->value)
			return (false);
		current = current->next;
	}
	return (true);
}

t_node	*find_node_by_idx(t_stack *stack, int idx)
{
	t_node	*current;

	if (!stack)
		return (NULL);
	current = stack->head;
	while (current)
	{
		if (current->index == idx)
			return (current);
		current = current->next;
	}
	return (NULL);
}

static int	calculate_cost(int stack_size, int position)
{
	int	cost_fwd;
	int	cost_rev;

	cost_fwd = position;
	cost_rev = stack_size - position;
	if (cost_rev < cost_fwd)
		return (cost_rev);
	else
		return (cost_fwd);
}

static void	upd_cheapest(t_node *candidate, int cost,
	t_node **cheapest_node, int *min_cost)
{
	if (*min_cost == -1 || cost < *min_cost)
	{
		*min_cost = cost;
		*cheapest_node = candidate;
	}
}

t_node	*find_cheapest_node(t_stack *stack, int max_idx)
{
	t_node	*current;
	t_node	*cheapest_node;
	int		min_cost;
	int		current_pos;
	int		cost;

	if (!stack || !stack->head)
		return (NULL);
	current = stack->head;
	cheapest_node = NULL;
	min_cost = -1;
	current_pos = 0;
	while (current)
	{
		if (current->index <= max_idx)
		{
			cost = calculate_cost(stack->size, current_pos);
			upd_cheapest(current, cost, &cheapest_node, &min_cost);
			if (min_cost == 0)
				break ;
		}
		current = current->next;
		current_pos++;
	}
	return (cheapest_node);
}
