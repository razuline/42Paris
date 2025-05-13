/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_list_size.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erazumov <erazumov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 19:44:04 by erazumov          #+#    #+#             */
/*   Updated: 2025/05/13 22:12:18 by erazumov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "ft_list.h"

int	ft_list_size(t_list *begin_list)
{
	int	count;

	count = 0;
	while (begin_list != NULL)
	{
		count++;
		begin_list = begin_list->next;
	}
	return (count);
}

/*
#include <stdio.h>

int	main(void)
{
	t_list	elem1, elem2, elem3;
	
	elem1.next = &elem2;
	elem2.next = &elem3;
	elem3.next = NULL;
	
	printf("List size: %d\n", ft_list_size(&elem1)); // 3
	printf("Empty list: %d\n", ft_list_size(NULL));  // 0
	
	return (0);
}
*/