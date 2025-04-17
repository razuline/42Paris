/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erazumov <erazumov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 16:36:51 by erazumov          #+#    #+#             */
/*   Updated: 2025/04/17 14:31:22 by erazumov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlen_gnl(char *str)
{
	size_t	i;

	i = 0;
	if (!str)
		return (0);
	while (str[i])
		i++;
	return (i);
}

char	*ft_str_join(char *remainder, char *buff)
{
	size_t	i;
	size_t	j;
	char	*result;

	if (!remainder)
	{
		remainder = (char *)malloc(sizeof(char) * 1);
		remainder[0] = '\0';
	}
	if (!remainder || !buff)
		return (NULL);
	result = malloc(sizeof(char) * ((ft_strlen(remainder)
					+ ft_strlen(buff)) + 1));
	if (result == NULL)
		return (NULL);
	i = -1;
	j = 0;
	if (remainder)
		while (remainder[++i] != '\0')
			result[i] = remainder[i];
	while (buff[j] != '\0')
		result[i++] = buff[j++];
	result[ft_strlen(remainder) + ft_strlen(buff)] = '\0';
	ft_if_error(remainder);
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
