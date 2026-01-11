/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstiter.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erazumov <erazumov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 11:22:08 by erazumov          #+#    #+#             */
/*   Updated: 2025/06/18 11:24:34 by erazumov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* Iterates through the list ’lst’ and applies the function ’f’ to the content
of each node.
lst: The address of a pointer to a node.
f: The address of the function to apply to each node’s content. */

#include "libft.h"

void	ft_lstiter(t_list *lst, void (*f)(void*))
{
	if (!f)
		return ;
	while (lst)
	{
		(*f)(lst->content);
		lst = lst->next;
	}
}
