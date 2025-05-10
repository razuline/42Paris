/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_list_foreach.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erazumov <erazumov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/10 15:57:36 by erazumov          #+#    #+#             */
/*   Updated: 2025/05/10 16:06:02 by erazumov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "ft_list.h"

void	ft_list_foreach(t_list *begin_list, void (*f)(void *))
{
	t_list	*curr;

	curr = begin_list;
	while (curr != NULL)
	{
		(*f)(curr->data);
		curr = curr->next;
	}
}
/*
#include <stdio.h>

void	print_string(void *data)
{
	printf("%s\n", (char*)data);
}

int	main(void)
{
	t_list	elem1, elem2, elem3;
	
	elem1.data = "Hello";
	elem1.next = &elem2;
	
	elem2.data = "World";
	elem2.next = &elem3;
	
	elem3.data = "!";
	elem3.next = NULL;
	
	ft_list_foreach(&elem1, &print_string);
	ft_list_foreach(NULL, &print_string);
	
	t_list	single;
	single.data = "Single";
	single.next = NULL;
	ft_list_foreach(&single, &print_string);
	
	return (0);
}
*/