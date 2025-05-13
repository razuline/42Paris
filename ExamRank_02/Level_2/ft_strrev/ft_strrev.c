/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrev.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erazumov <erazumov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 14:56:05 by erazumov          #+#    #+#             */
/*   Updated: 2025/05/13 15:23:51 by erazumov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

char	*ft_strrev(char *str)
{
	int		tmp;
	char	*start;
	char	*end;

	if (!str)
		return (NULL);
	start = str;
	end = str;
	while (*end)
		end++;
	end--;
	while (start < end)
	{
		tmp = *start;
		*start = *end;
		*end = tmp;
		start++;
		end--;
	}
	return (str);
}
/*
#include <stdio.h>
#include <string.h>

int	main(void)
{
	char	test1[] = "Hello";
	char	test2[] = "";
	char	test3[] = "a";
	char	test4[] = "12345";
	char	*test5 = NULL;

	printf("Before: '%s'\n", test1);
	printf("After:  '%s'\n\n", ft_strrev(test1));

	printf("Before: '%s'\n", test2);
	printf("After:  '%s'\n\n", ft_strrev(test2));

	printf("Before: '%s'\n", test3);
	printf("After:  '%s'\n\n", ft_strrev(test3));

	printf("Before: '%s'\n", test4);
	printf("After:  '%s'\n\n", ft_strrev(test4));

	printf("Test NULL: %s\n", ft_strrev(test5));

	return (0);
}
*/