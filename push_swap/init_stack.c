/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_stack.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erazumov <erazumov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 17:46:34 by erazumov          #+#    #+#             */
/*   Updated: 2025/03/09 14:35:57 by erazumov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "push_swap.h"

/* Create an empty stack */
t_stack	*init_stack(void)
{
	t_stack	*stack;

	stack = (t_stack *)malloc(sizeof(t_stack));
	if (!stack)
		return (NULL);
	stack->head = NULL;
	stack->tail = NULL;
	stack->size = 0;
	return (stack);
}

/* Free mamory of a stack */
void	free_stack(t_stack *stack)
{
	t_node	*current;
	t_node	*tmp;

	if (!stack)
		return ;
	current = stack->head;
	while (current)
	{
		tmp = current->next;
		free(current);
		current = tmp;
	}
	free(stack);
}

/* Add a new element at the end of a stack */
void	push_to(t_stack *stack, int value)
{
	t_node	*new_node;

	new_node = (t_node *)malloc(sizeof(t_node));
	if (!new_node)
		if_error("Error!\n");
	new_node->value = value;
	new_node->prev = stack->tail;
	new_node->next = NULL;
	if (stack->tail)
		stack->tail->next = new_node;
	else
		stack->head = new_node;
	stack->tail = new_node;
	stack->size++;
}

/* Delete and return the last element of the stack */
int	pop(t_stack *stack)
{
	int		value;
	t_node	*tmp;

	if (!stack->tail)
		if_error("Error!\n");
	tmp = stack->tail;
	value = tmp->value;
	stack->tail = tmp->prev;
	if (stack->tail)
		stack->tail->next = NULL;
	else
		stack->head = NULL;
	free(tmp);
	stack->size--;
	return (value);
}

/* */
void	parse_input(t_stack *stack, char **av)
{
	int		i;
	int		j;
	int		nb;
	char	**nbrs;

	i = 1;
	while (av[i])
	{
		nbrs = ft_split(av[i], ' ');
		if (!nbrs)
			if_error("Error!\n");
		j = 0;
		while (nbrs[j])
		{
			nb = ft_atoi(nbrs[j]);
			push_to(stack, nb);
			free(nbrs[j]);
			j++;
		}
		free(nbrs);
		i++;
	}
}
