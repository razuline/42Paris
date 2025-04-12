/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erazumov <erazumov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 14:35:03 by erazumov          #+#    #+#             */
/*   Updated: 2025/04/12 10:57:18 by erazumov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	push(t_stack *dst, t_stack *src)
{
	t_node	*node;

	if (!src || !src->head)
		return ;
	node = src->head;
	src->head = node->next;
	if (src->head)
		src->head->prev = NULL;
	else
		src->tail = NULL;
	node->next = dst->head;
	if (dst->head)
		dst->head->prev = node;
	else
		dst->tail = node;
	dst->head = node;
	src->size--;
	dst->size++;
}

void	pa(t_stack *a, t_stack *b)
{
	push(a, b);
	ft_printf("pa\n");
}

void	pb(t_stack *a, t_stack *b)
{
	push(b, a);
	ft_printf("pb\n");
}
