/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erazumov <erazumov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/16 15:03:46 by erazumov          #+#    #+#             */
/*   Updated: 2024/11/26 15:09:20 by erazumov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* Allocates (with malloc(3)) and returns a copy of ’s1’ with the characters 
specified in ’set’ removed from the beginning and the end of the string.
s1: The string to be trimmed.
set: The reference set of characters to trim.
Returns the trimmed string or NULL if the allocation fails. */

#include "libft.h"

static int	ft_in_set(char c, char const *set)
{
	int	i;

	i = 0;
	while (set[i])
	{
		if (c == set[i])
			return (1);
		i++;
	}
	return (0);
}

char	*ft_strtrim(char const *s1, char const *s2)
{
	int	begin;
	int	end;

	if (!s1)
		return (NULL);
	begin = 0;
	end = ft_strlen(s1) - 1;
	while (s1[begin] && ft_in_set(s1[begin], s2))
		begin++;
	while (s1[end] && ft_in_set(s1[end], s2))
		end--;
	if (end == -1)
		return (ft_substr(s1, begin, 0));
	return (ft_substr(s1, begin, (end - begin + 1)));
}
