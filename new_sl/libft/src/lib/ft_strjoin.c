/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erazumov <erazumov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 15:55:40 by erazumov          #+#    #+#             */
/*   Updated: 2024/11/24 16:40:58 by erazumov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* Allocates (with malloc(3)) and returns a new string, which is the result 
of the concatenation of ’s1’ and ’s2’.
s1: The prefix string.
s2: The suffix string.
Returns the new string or NULL if the allocation fails. */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	int		i;
	int		len1;
	int		len2;
	char	*result;

	if (!s1 || !s2)
		return (NULL);
	len1 = ft_strlen(s1);
	len2 = ft_strlen(s2);
	result = (char *)malloc(sizeof(char) * (len1 + len2 + 1));
	if (!result)
		return (NULL);
	i = 0;
	while (s1[i])
	{
		result[i] = s1[i];
		i++;
	}
	i = 0;
	while (s2[i])
	{
		result[len1++] = s2[i++];
	}
	result[len1] = '\0';
	return (result);
}
/*
#include <stdio.h>

int	main(void)
{
	char	*res;
	char	*s1 = "peanut ";
	char	*s2 = "butter";
	
	res = ft_strjoin(s1, s2);
	printf("%s\n", res);
	free(res);
	return (0);
}
*/