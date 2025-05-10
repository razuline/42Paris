/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_list_remove_if.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erazumov <erazumov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/10 16:11:29 by erazumov          #+#    #+#             */
/*   Updated: 2025/05/10 16:31:31 by erazumov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "ft_list.h"

void	ft_list_remove_if(t_list **begin_list, void *data_ref,
			int (*cmp)(void *, void *))
{
	t_list	*curr;
	t_list	*prev;
	t_list	*to_delete;

	curr = *begin_list;
	prev = NULL;
	to_delete = NULL;
	while (curr != NULL)
	{
		if (cmp(curr->data, data_ref) == 0)
		{
			if (prev == NULL)
			{
				to_delete = *begin_list;
				*begin_list = (*begin_list)->next;
				curr = *begin_list;
			}
			else
			{
				to_delete = curr;
				prev->next = curr->next;
				curr = curr->next;
			}
			free(to_delete);
		}
		else
		{
			prev = curr;
			curr = curr->next;
		}
	}
}
/*
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

int	compare_strings(void *a, void *b)
{
	return (strcmp((char*)a, (char*)b));
}

void	print_list(t_list *list)
{
	while (list != NULL)
	{
		printf("%s -> ", (char*)list->data);
		list = list->next;
	}
	printf("NULL\n");
}

t_list	*create_node(void *data)
{
	t_list	*node = malloc(sizeof(t_list));
	if (node == NULL)
		return (NULL);
	node->data = data;
	node->next = NULL;
	return (node);
}

void	free_list(t_list *list)
{
	t_list	*tmp;
	while (list != NULL)
	{
		tmp = list;
		list = list->next;
		free(tmp);
	}
}

int	main(void)
{
	// Create list with malloc
	t_list *list = create_node("Test");
	list->next = create_node("Hello");
	list->next->next = create_node("World");
	
	printf("Before: ");
	print_list(list);
	
	// Delete "Hello"
	ft_list_remove_if(&list, "Hello", &compare_strings);
	
	printf("After: ");
	print_list(list);

	free_list(list);
	
	return (0);
}
*/