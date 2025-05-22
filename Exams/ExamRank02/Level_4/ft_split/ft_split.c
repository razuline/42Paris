/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erazumov <erazumov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/10 14:26:42 by erazumov          #+#    #+#             */
/*   Updated: 2025/05/22 13:43:00 by erazumov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

static int	is_space(char c)
{
	return (c == ' ' || c == '\t' || c == '\n');
}

static int	words_count(char *str)
{
	int	count;
	int	in_word;

	count = 0;
	in_word = 0;

	while (*str)
	{
		if (!is_space(*str) && !in_word)
		{
			in_word = 1;
			count++;
		}
		else if (is_space(*str))
			in_word = 0;
		str++;
	}
	return (count);
}

static char	*word_copy(char *str)
{
	int		i;
	int		len;
	char	*word;

	len = 0;
	while (str[len] && !is_space(str[len]))
		len++;
	
	word = (char *)malloc(sizeof(char) * (len + 1));
	if (!word)
		return (NULL);
	
	i = 0;
	while (i < len)
	{
		word[i] = str[i];
		i++;
	}
	word[len] = '\0';
	return (word);
}

char	**ft_split(char *str)
{
	int		i;
	int		words;
	char	**result;

	if (!str)
		return (NULL);
	
	words = words_count(str);

	result = (char **)malloc(sizeof(char *) * (words + 1));
	if (!result)
		return (NULL);

	i = 0;
	while (*str)
	{
		while (*str && is_space(*str))
			str++;

		if (!*str)
			break ;
		
		result[i] = word_copy(str);
		if (!result[i])
		{
			while (i-- > 0)
				free(result[i]);
			free(result);
			return (NULL);
		}
		i++;

		while (*str && !is_space(*str))
			str++;
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