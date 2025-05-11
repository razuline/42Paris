/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erazumov <erazumov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/10 17:44:23 by erazumov          #+#    #+#             */
/*   Updated: 2025/05/11 11:09:37 by erazumov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_strlen(char *str)
{
	int	len;

	len = 0;
	while(str[len] != '\0')
		len++;
	return (len);
}
/*
#include <stdio.h>
#include <string.h>

int	main(void)
{
	// Test 1: Plain string
	char	*test1 = "Hello";
	printf("Test 1: \"%s\"\n", test1);
	printf("Expected: %lu, Got: %d\n", strlen(test1), ft_strlen(test1));
	
	// Test 2: Empty string
	char	*test2 = "";
	printf("\nTest 2: \"%s\"\n", test2);
	printf("Expected: %lu, Got: %d\n", strlen(test2), ft_strlen(test2));
	
	// Test 3: Long string
	char	*test3 = "This is a very long string for testing purposes";
	printf("\nTest 3: Long string\n");
	printf("Expected: %lu, Got: %d\n", strlen(test3), ft_strlen(test3));
	
	// Test 4: String with spaces
	char	*test4 = "   Spaces   ";
	printf("\nTest 4: \"%s\"\n", test4);
	printf("Expected: %lu, Got: %d\n", strlen(test4), ft_strlen(test4));
	
	// Test 5: Special characters
	char	*test5 = "\t\n\v\f\r";
	printf("\nTest 5: Special characters\n");
	printf("Expected: %lu, Got: %d\n", strlen(test5), ft_strlen(test5));
	
	return (0);
}
*/