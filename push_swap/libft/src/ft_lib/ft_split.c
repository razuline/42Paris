/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erazumov <erazumov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/16 15:43:06 by erazumov          #+#    #+#             */
/*   Updated: 2024/11/24 16:43:15 by erazumov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* Allocates (with malloc(3)) and returns an array of strings obtained 
by splitting ’s’ using the character ’c’ as a delimiter. The array must end 
with a NULL pointer.
str: The string to be split.
sep: The delimiter character.
Returns the array of new strings resulting from the split or NULL if 
the allocation fails.*/

#include "libft.h"

static char	**ft_malloc_error(char **arr)
{
	int	i;

	i = 0;
	while (arr[i])
		free(arr[i++]);
	free(arr);
	return (NULL);
}

static int	ft_wordcount(char const *str, char c)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (str[i])
	{
		if (str[i] == c)
			i++;
		else
		{
			count++;
			while (str[i] != c && str[i])
				i++;
		}
	}
	return (count);
}

static char	*ft_getword(char const *str, int *idx, char c)
{
	char	*new;
	int		word_len;
	int		i;

	word_len = 0;
	while (str[*idx] == c)
		(*idx)++;
	i = *idx;
	while (str[i] && str[i] != c)
	{
		word_len++;
		i++;
	}
	new = malloc(sizeof(char) * (word_len + 1));
	if (!new)
		return (NULL);
	i = 0;
	while (str[*idx] && str[*idx] != c)
		new[i++] = str[(*idx)++];
	new[i] = '\0';
	return (new);
}

char	**ft_split(char const *str, char sep)
{
	char	**split;
	int		wdct;
	int		idx;
	int		i;

	i = 0;
	idx = 0;
	if (!str)
		return (NULL);
	wdct = ft_wordcount(str, sep);
	split = malloc(sizeof(char *) * (wdct + 1));
	if (!split)
		return (NULL);
	while (i < wdct)
	{
		split[i] = ft_getword(str, &idx, sep);
		if (!split[i])
			return (ft_malloc_error(split));
		i++;
	}
	split[i] = 0;
	return (split);
}
/*
#include <stdio.h>

int	main(void)
{
	char	*str;
	char	sep;
	char	**res;

	str = " C'e stl avi e. ";
	sep = ' ';
	printf("%d\n", ft_wordcount(str, sep));
	res = ft_split(str, sep);
	while (*res)
	{
		printf("%s\n", *res);
		res++;
	}
	return (0);
}
*/