/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erazumov <erazumov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/15 20:54:28 by razuline          #+#    #+#             */
/*   Updated: 2024/11/26 15:13:33 by erazumov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* Applies the function f to each character of the string s, passing its index
as the first argument and the character itself as the second. A new string is
created (using malloc(3)) to collect the results from the successive
applications of f.
The string created from the successive applications of ’f’.
Returns NULL if the allocation fails. */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	unsigned int	i;
	char			*res;

	if (!s || !f)
		return (NULL);
	i = 0;
	res = (char *)malloc(sizeof(char) * (ft_strlen(s) + 1));
	if (!res)
		return (NULL);
	while (s[i])
	{
		res[i] = f(i, s[i]);
		i++;
	}
	res[i] = '\0';
	return (res);
}
/*
#include <stdio.h>

void	f(unsigned int i, char *s)
{
	unsigned int	n;
	
	n = i;
	*s = 'a';
}

int	main(void)
{
	char	*str = "Hello";

	ft_strmapi(str, f);
	printf("%s\n", str);
	return (0);
}
*/