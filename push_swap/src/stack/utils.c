/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erazumov <erazumov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 13:15:41 by erazumov          #+#    #+#             */
/*   Updated: 2025/04/09 14:08:25 by erazumov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../includes/push_swap.h"

t_node	*new_node(int value)
{
	t_node	*node;

	node = (t_node *)malloc(sizeof(t_node));
	if (!node)
		if_error("Error: Memory allocation failed!\n");
	node->value = value;
	node->prev = NULL;
	node->next = NULL;
	return (node);
}

int	is_sorted(t_stack *stack)
{

}

void	if_error(const char *str)
{
	if (str)
		write(2, str, ft_strlen(str));
	write(2, "\n", 1);
	exit(1);
}

int	find_min(t_stack *stack)
{
	int		min;
	t_node	*current;

	current = stack->head;
	min = current->value;
	while (current)
	{
		if (current->value < min)
			min = current->value;
		current = current->next;
	}
	return (min);
}

int	find_target_position(t_stack *a, int value)
{
	t_node	*current;
	int		pos;
	int		target_pos;

	current = a->head;
	pos = 0;
	target_pos = 0;
	while (current)
	{
		if (current->value > value)
		{
			target_pos = pos;
			break ;
		}
		pos++;
		current = current->next;
	}
	return (target_pos);
}
