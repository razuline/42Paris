/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   swap.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erazumov <erazumov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 13:26:09 by erazumov          #+#    #+#             */
/*   Updated: 2025/03/07 14:52:56 by erazumov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../push_swap.h"

void	sa(t_elem **stack, int a)
{
	int		tmp;
	t_elem	*node;

	node = *stack;
	tmp = node->number;
	node->number = node->next->number;
	node->next->number = tmp;
	tmp = node->index;
	node->index = node->next->index;
	node->next->index = tmp;
	if (a)
		ft_printf("sa\n");
}

void	sb(t_elem **stack, int a)
{
	int		tmp;
	t_elem	*node;

	node = *stack;
	tmp = node->number;
	node->number = node->next->number;
	node->next->number = tmp;
	tmp = node->index;
	node->index = node->next->index;
	node->next->index = tmp;
	if (a)
		ft_printf("sb\n");
}
