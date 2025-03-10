/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erazumov <erazumov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 18:11:00 by erazumov          #+#    #+#             */
/*   Updated: 2025/03/10 18:13:08 by erazumov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "checker.h"

void	free_stack(t_stack *stack)
{
	t_stack	*tmp;
	while (stack)
	{
		tmp = stack;
		stack = stack->next;
		free(tmp);
	}
}

void	if_error(void)
{
	ft_putstr_fd("Error\n", 2);
	exit(1);
}

int	is_empty(t_stack *stack)
{
	return (stack == NULL);
}

int	is_sorted(t_stack *a)
{
	t_stack	*current;

	if (!a)
		return (1);
	current = a;
	while (current->next)
	{
		if (current->value > current->next->value)
			return (0);
		current = current->next;
	}
	return (1);
}
