/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_list.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erazumov <erazumov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/10 16:34:45 by erazumov          #+#    #+#             */
/*   Updated: 2025/05/10 17:08:45 by erazumov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "ft_list.h"

void	swap_data(t_list *a, t_list *b)
{
	int	tmp;
	
	tmp = a->data;
	a->data = b->data;
	b->data = tmp;
}

t_list	*sort_list(t_list *lst, int (*cmp)(int, int))
{
	int		swapped;
	t_list	*curr;
	t_list	*prev;

	if (!lst || !lst->next)
		return (lst);

	swapped = 1;
	prev = NULL;
	while (swapped)
	{
		swapped = 0;
		curr = lst;

		while (curr->next != prev)
		{
			if (!cmp(curr->data, curr->next->data))
			{
				swap_data(curr, curr->next);
				swapped = 1;
			}
			curr = curr->next;
		}
		prev = curr;
	}
	return (lst);
}
/*
#include <stdio.h>
#include <stdlib.h>

int	ascending(int a, int b)
{
	return (a <= b);
}

int	main(void)
{
	// Create a list: 3 -> 1 -> 4 -> 2
	t_list nodes[4] = {
		{3, &nodes[1]},
		{1, &nodes[2]},
		{4, &nodes[3]},
		{2, NULL}
	};
	
	printf("Before: ");
	for (t_list *p = nodes; p; p = p->next)
		printf("%d -> ", p->data);
	printf("NULL\n");
	
	sort_list(nodes, &ascending);
	
	printf("After: ");
	for (t_list *p = nodes; p; p = p->next)
		printf("%d -> ", p->data);
	printf("NULL\n");
	
	return (0);
}
*/