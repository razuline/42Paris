/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erazumov <erazumov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 18:30:58 by erazumov          #+#    #+#             */
/*   Updated: 2025/03/09 09:48:27 by erazumov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../push_swap.h"

void	if_error(const char *str)
{
	if (str)
		write(2, str, ft_strlen(str));
	write(2, "\n", 1);
	exit(1);
}

void	parse_args(t_stack *a, char **av)
{
	int	i;
	int	value;

	i = 1;
	while (av[i])
	{
		value = ft_atoi(av[i]);
		push_to(a, value);
		i++;
	}
}

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
