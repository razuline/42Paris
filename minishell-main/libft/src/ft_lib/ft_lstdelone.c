/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdelone.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erazumov <erazumov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 11:17:00 by erazumov          #+#    #+#             */
/*   Updated: 2025/06/18 11:18:33 by erazumov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* Takes a node as parameter and frees its content using the function ’del’.
Free the node itself but does NOT free the next node.
lst: The node to free.
del: The address of the function used to delete the content. */

#include "libft.h"

void	ft_lstdelone(t_list *lst, void (*del)(void*))
{
	if (!del)
		return ;
	if (lst)
	{
		(*del)(lst->content);
		free(lst);
	}
}
