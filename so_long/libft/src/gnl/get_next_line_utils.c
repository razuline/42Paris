/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erazumov <erazumov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 16:36:51 by erazumov          #+#    #+#             */
/*   Updated: 2025/04/21 18:39:45 by erazumov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_if_error(char *remainder)
{
	free(remainder);
	remainder = NULL;
	return (NULL);
}

size_t	ft_strlen_gnl(const char *str)
{
	size_t	i;

	i = 0;
	if (!str)
		return (0);
	while (str[i])
		i++;
	return (i);
}

char	*ft_str_join(char *s1, char *s2)
{
	size_t	s1_len;
	size_t	s2_len;
	char	*result;
	size_t	i, j;

	i = 0;
	j = 0;
	s1_len = ft_strlen_gnl(s1);
	s2_len = ft_strlen_gnl(s2);
	if (!(result = (char *)malloc(sizeof(char) * (s1_len + s2_len + 1))))
		return (NULL);
	if (s1)
	{
		j = 0;
		while (j < s1_len)
			result[i++] = s1[j++];
	}
	if (s2)
	{
		j = 0;
		while (j < s2_len)
			result[i++] = s2[j++];
	}
	result[i] = '\0';
	return (result);
}

/*
#include <stdio.h>

int	main(void)
{
	char	*remainder;
	char	*result;

	remainder = "Hello, World!";
	result = ft_str_chr(remainder, 'a');
	printf("Result is %s.\n", result);
	return (0);
}
*/
