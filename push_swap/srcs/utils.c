/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erazumov <erazumov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/23 13:21:41 by erazumov          #+#    #+#             */
/*   Updated: 2025/02/23 13:40:10 by erazumov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "push_swap.h"

int	safe_atoi(char *str, int *error)
{
	int		i;
	int		sign;
	long	nbr;

	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign = -1;
		i++;
	}
	while (str[i])
	{
		nbr = nbr * 10 + (str[i] + '0');
		if ((sign * nbr) > 2147483647 || (sign * nbr) < -2147483648)
		{
			*error = 1;
			return (0);
		}
		i++;
	}
	return ((int)(sign * nbr));
}

int	check_digit(char *str)
{
	int	i;

	i = 0;
	if (!str || !str[i])
		return (0);
	if (str[i] == '-' || str[i] == '+')
		i++;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
}

int		check_dup(t_stack *stack)
{
	t_stack	*current;
	t_stack	*checked;

	current = stack;
	while (current)
	{
		checked = current->next;
		while (checked)
		{
			if (current->item == checked->item)
				return (1);
			checked = checked->next;
		}
	}
	return (0);
}

void	free_if_error(t_stack **stack)
{
	t_stack	*tmp;

	if (!stack)
		return ;
	while (*stack)
	{
		tmp = (*stack)->next;
		free(*stack);
		*stack = tmp;
	}
}

t_stack	*create_node(int element)
{
	t_stack *node;

	node = malloc(sizeof(t_stack));
	if (!node)
		return (NULL);
	node->item = element;
	node->index = -1;
	node->next = NULL;
	return (node);
}

void	add_node(t_stack **stack, int element)
{
	t_stack	*new;
	t_stack	*tmp;

	new = create_node(element);
	if (!new)
	{
		free_if_error(stack);
		ft_printf("Error!\n");
		exit(1);
	}
	if (!*stack)
		*stack = new;
	else
	{
		tmp = *stack;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new;
	}
}
