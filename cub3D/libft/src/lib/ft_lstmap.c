/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erazumov <erazumov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 11:25:31 by erazumov          #+#    #+#             */
/*   Updated: 2025/06/18 11:28:39 by erazumov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* Iterates through the list ’lst’, applies the function ’f’ to each node’s
content, and creates a new list resulting of the successive applications of the
function ’f’. The ’del’ function is used to delete the content of a node
if needed.
lst: The address of a pointer to a node.
f: The address of the function applied to each node’s content.
del: The address of the function used to delete a node’s content if needed.
Return value: The new list. NULL if the allocation fails. */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void*), void (*del)(void *))
{
	t_list	*first;
	t_list	*new;

	if (!f || !del)
		return (NULL);
	first = NULL;
	while (lst)
	{
		new = ft_lstnew((*f)(lst->content));
		if (!new)
		{
			while (first)
			{
				new = first->next;
				(*del)(first->content);
				free(first);
				first = new;
			}
			lst = NULL;
			return (NULL);
		}
		ft_lstadd_back(&first, new);
		lst = lst->next;
	}
	return (first);
}
