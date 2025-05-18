/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erazumov <erazumov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 14:40:13 by erazumov          #+#    #+#             */
/*   Updated: 2025/05/13 21:17:28 by erazumov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

char	*ft_strdup(char *src)
{
	int		i;
	int		len;
	char	*dest;

	if (!src)
		return (NULL);
	len = 0;
	while (src[len])
		len++;
	dest = malloc(len + 1);
	if (!dest)
		return (NULL);
	i = 0;
	while (i < len)
	{
		dest[i] = src[i];
		i++;
	}
	dest[len] = '\0';
	return (dest);
}

/*
#include <stdio.h>
#include <string.h>

int	main(void)
{
	char	*str;
	char	*copy;

	// Test 1: Normal string
	str = "Hello World!";
	copy = ft_strdup(str);
	printf("Original: '%s'\nCopy:     '%s'\n\n", str, copy);
	free(copy);

	// Test 2: Empty string
	str = "";
	copy = ft_strdup(str);
	printf("Original: '%s'\nCopy:     '%s'\n\n", str, copy);
	free(copy);

	// Test 3: NULL pointer
	str = NULL;
	copy = ft_strdup(str);
	printf("Original: NULL\nCopy:     %s\n\n", copy ? "NOT NULL" : "NULL");

	// Test 4: Long string
	char	long_str[1000];
	memset(long_str, 'A', 999);
	long_str[999] = '\0';
	copy = ft_strdup(long_str);
	printf("Long string copy %s\n", 
		strlen(long_str) == strlen(copy) ? "OK" : "FAIL");
	free(copy);

	return (0);
}
*/