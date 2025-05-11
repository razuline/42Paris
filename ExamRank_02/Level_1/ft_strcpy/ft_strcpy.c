/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erazumov <erazumov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/10 17:45:09 by erazumov          #+#    #+#             */
/*   Updated: 2025/05/11 11:14:00 by erazumov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

char	*ft_strcpy(char *s1, char *s2)
{
	int	i;

	if (!s1 || !s2)
		return (NULL);

	i = 0;
	while (s2[i] != '\0')
	{
		s1[i] = s2[i];
		i++;
	}
	s1[i] = '\0';
	return (s1);
}
/*
#include <stdio.h>
#include <string.h>

#define BUF_SIZE 50

void	run_test(char *test_name, char *src)
{
	char	std_dest[BUF_SIZE];
	char	ft_dest[BUF_SIZE];
	
	// Clean buffers
	memset(std_dest, 0, BUF_SIZE);
	memset(ft_dest, 0, BUF_SIZE);
	
	// Copying
	strcpy(std_dest, src);
	ft_strcpy(ft_dest, src);
	
	// Check result
	printf("Test '%s':\n", test_name);
	printf("  Source: \"%s\"\n", src);
	printf("  strcpy: \"%s\"\n", std_dest);
	printf("  ft_strcpy: \"%s\"\n", ft_dest);
	
	if (strcmp(std_dest, ft_dest) == 0)
		printf("  \033[0;32mOK\033[0m\n\n");
	else
		printf("  \033[0;31mFAIL\033[0m\n\n");
}

int	main(void)
{
	// Test 1: Plain string
	run_test("Normal string", "Hello World!");
	
	// Test 2: Empty string
	run_test("Empty string", "");
	
	// Test 3: String with spaces
	run_test("String with spaces", "   Test   ");
	
	// Test 4: Special characters
	run_test("Special characters", "\t\n\v\f\r");
	
	// Test 5: Long string
	char	long_str[BUF_SIZE - 1];
	memset(long_str, 'A', BUF_SIZE - 2);
	long_str[BUF_SIZE - 2] = '\0';
	run_test("Long string", long_str);
	
	return (0);
}
*/