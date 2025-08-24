/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstlast.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erazumov <erazumov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 11:12:09 by erazumov          #+#    #+#             */
/*   Updated: 2025/06/18 11:13:38 by erazumov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* Returns the last node of the list.
lst: The beginning of the list.
Return value: Last node of the list.*/

#include "libft.h"

t_list	*ft_lstlast(t_list *lst)
{
	while (lst)
	{
		if (!lst->next)
			return (lst);
		lst = lst->next;
	}
	return (lst);
}
