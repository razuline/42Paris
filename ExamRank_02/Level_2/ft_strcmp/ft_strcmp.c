/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erazumov <erazumov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 14:26:59 by erazumov          #+#    #+#             */
/*   Updated: 2025/05/13 14:54:37 by erazumov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_strcmp(char *s1, char *s2)
{
	while (*s1 && *s1 == *s2)
	{
		s1++;
		s2++;
	}
	return (*(unsigned char *)s1 - *(unsigned char *)s2);
}
/*
#include <stdio.h>
#include <string.h>

void	run_test(char *s1, char *s2)
{
	int	std = strcmp(s1, s2);
	int	ft = ft_strcmp(s1, s2);
	int	result = (std == ft) || (std * ft > 0); // Same sign or both zero
	
	printf("Test: \"%s\" vs \"%s\"\n", s1, s2);
	printf("strcmp: %d, ft_strcmp: %d - ", std, ft);
	printf(result ? "\033[0;32mOK\033[0m\n" : "\033[0;31mFAIL\033[0m\n");
}

int	main(void)
{
	// Equal strings
	run_test("", "");
	run_test("hello", "hello");
	
	// Different cases
	run_test("hello", "HELLO");
	run_test("apple", "banana");
	
	// Substrings
	run_test("hello", "hello world");
	run_test("short", "shorter");
	
	// Special characters
	run_test("\xff", "\x01");  // Test unsigned char comparison
	run_test("\200", "\0");
	
	// Real-world examples
	run_test("42", "42");
	run_test("abc", "abd");
	run_test("abc", "abcd");
	
	return (0);
}
*/