/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erazumov <erazumov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/10 14:26:42 by erazumov          #+#    #+#             */
/*   Updated: 2025/05/13 22:14:45 by erazumov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

int	is_space(char c)
{
	return (c == ' ' || c == '\t' || c == '\n');
}

int	count_words(char *str)
{
	int	count;

	count = 0;
	while (*str)
	{
		while (is_space(*str))
			str++;
		if (*str)
			count++;
		while (*str && !is_space(*str))
			str++;
	}
	return (count);
}

char	**ft_split(char *str)
{
	int		i;
	int		j;
	int		len;
	int		words;
	char	*start;
	char	**result;

	if (!str)
		return (NULL);

	words = count_words(str);
	result = malloc(sizeof(char *) * (words + 1));
	if (!result)
		return (NULL);

	i = 0;
	while (*str)
	{
		while (is_space(*str))
			str++;
		if (!*str)
			break ;
		
		start = str;
		while (*str && !is_space(*str))
			str++;
		len = str - start;

		result[i] = malloc(len + 1);
		if (!result[i])
		{
			while (i > 0)
				free(result[--i]);
			free(result);
			return (NULL);
		}
		
		j = 0;
		while (j < len)
		{
			result[i][j] = start[j];
			j++;
		}
		result[i++][len] = '\0';
	}
	result[i] = NULL;
	return (result);
}

/*
#include <stdio.h>

void	print_split_result(char *str)
{
	printf("Input: \"%s\"\n", str);
	char	**result = ft_split(str);
	
	if (!result)
	{
		printf("Error: ft_split returned NULL\n\n");
		return ;
	}
	for (int i = 0; result[i]; i++)
	{
		printf("Word %d: \"%s\"\n", i, result[i]);
		free(result[i]);  // Free each word
	}
	free(result);  // Free the array
	printf("\n");
}

int	main(void)
{
	// Test 1: Normal string
	print_split_result("Hello world  from ft_split");

	// Test 2: Empty string
	print_split_result("");

	// Test 3: Only whitespace
	print_split_result("   \t\n  ");

	// Test 4: Single word
	print_split_result("OneWord");

	// Test 5: Multiple spaces between words
	print_split_result("Too    many   spaces");

	return (0);
}
*/