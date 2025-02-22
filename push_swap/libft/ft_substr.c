/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erazumov <erazumov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/16 14:34:35 by erazumov          #+#    #+#             */
/*   Updated: 2024/11/24 16:40:31 by erazumov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* Allocates (with malloc(3)) and returns a substring from the string ’s’.
The substring begins at index ’start’ and is of maximum size ’len’.
s: The string from which to create the substring.
start: The start index of the substring in the string ’s’.
len: The maximum length of the substring. 
Returns the substring or NULL if the allocation fails. */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	i;
	char	*substr;

	i = 0;
	if (!s)
		return (NULL);
	if (start >= ft_strlen(s))
		return ((char *)ft_calloc(1, sizeof(char)));
	if (start + len >= ft_strlen(s))
		substr = (char *)malloc(sizeof(char) * (ft_strlen(s) - start + 1));
	else
		substr = (char *)malloc(sizeof(char) * (len + 1));
	if (!substr)
		return (NULL);
	while (s[start] && i < len)
		substr[i++] = s[start++];
	substr[i] = '\0';
	return (substr);
}
/*
#include <stdio.h>

int	main(void)
{
	char	*str;
	char	*substr;

	str = "C'est la vie.";
	substr = ft_substr(str, 6, 10);
	printf("Substring : %s\n", substr);
	return (0);
}
*/