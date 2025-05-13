/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strpbrk.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erazumov <erazumov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 15:32:47 by erazumov          #+#    #+#             */
/*   Updated: 2025/05/13 17:53:43 by erazumov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

char	*ft_strpbrk(const char *s1, const char *s2)
{
	const char	*s1_ptr;
	const char	*s2_ptr;

	s1_ptr = s1;
	while (*s1_ptr)
	{
		s2_ptr = s2;
		while (*s2_ptr)
		{
			if (*s1_ptr == *s2_ptr)
				return ((char *)s1_ptr);
			s2_ptr++;
		}
		s1_ptr++;
	}
	return (NULL);
}
/*
#include <stdio.h>
#include <string.h>
#include <stddef.h>

// Helper function to run tests and print results
void	run_test(int test_num, const char *s1, const char *s2, const char *description) {
	char	*my_result = ft_strpbrk(s1, s2);
	char	*std_result = strpbrk(s1, s2); // Using standard strpbrk for comparison

	printf("Test %d: s1 = \"%s\", s2 = \"%s\"\n", test_num, s1, s2);
	printf("Description: %s\n", description);

	// Print what each function returned
	if (my_result != NULL) {
		printf("  ft_strpbrk: found '%c' (at address %p, substring: \"%s\")\n", *my_result, (void*)my_result, my_result);
	} else {
		printf("  ft_strpbrk: NULL\n");
	}
	if (std_result != NULL) {
		printf("  strpbrk   : found '%c' (at address %p, substring: \"%s\")\n", *std_result, (void*)std_result, std_result);
	} else {
		printf("  strpbrk   : NULL\n");
	}

	// Compare the pointers
	if (my_result == std_result) {
		printf("  Result: \033[32mOK\033[0m\n");
	} else {
		printf("  Result: \033[31mFAIL\033[0m\n");
	}
	printf("----------------------------------------\n");
}

int	main(void)
{
	int	test_count = 0;

	// --- Basic test cases ---
	run_test(++test_count, "hello world", "o", "Find first 'o'");
	run_test(++test_count, "hello world", "ol", "Find first 'o' or 'l' (l comes first)");
	run_test(++test_count, "hello world", "wo", "Find first 'w' or 'o' (o comes first)");
	run_test(++test_count, "tripouille", "p", "Find 'p'");
	run_test(++test_count, "tripouille", "iou", "Find 'i', 'o', or 'u' (i comes first)");
	run_test(++test_count, "abcdef", "xzy", "No match");
	run_test(++test_count, "abcdef", "c", "Match 'c'");
	run_test(++test_count, "abcdef", "f", "Match 'f' (at the end)");
	run_test(++test_count, "abcdef", "a", "Match 'a' (at the beginning)");

	// --- Edge cases (empty strings) ---
	run_test(++test_count, "", "abc", "s1 is empty");
	run_test(++test_count, "abc", "", "s2 is empty");
	run_test(++test_count, "", "", "Both s1 and s2 are empty");

	// --- More complex cases ---
	run_test(++test_count, "banana", "na", "s2 has 'n' and 'a', 'a' appears first in s1");
	run_test(++test_count, "banana", "b", "Match 'b' at the start");
	run_test(++test_count, "banana", "x", "No match in s1");
	run_test(++test_count, "test", "es", "Match 'e'");
	run_test(++test_count, "test", "st", "Match 's'"); // 's' appears before 't' in "test"
	run_test(++test_count, "abCDef", "CD", "Case sensitive match 'C'");
	run_test(++test_count, "abCDef", "dD", "Case sensitive match 'D'");
	run_test(++test_count, "abCDef", "cd", "No match due to case sensitivity");

	// --- s2 contains characters not in s1, but also one that is ---
	run_test(++test_count, "hello", "xyzl", "Match 'l'");
	run_test(++test_count, "hello", "lx", "Match 'l'");

	// --- s1 and s2 are the same ---
	run_test(++test_count, "example", "example", "s1 and s2 are identical");

	// --- Long string test ---
	char	long_s1[50];
	strcpy(long_s1, "aaaaaaaaaaaaaaaaaaaaaaaaab"); // 25 'a's then 'b'
	run_test(++test_count, long_s1, "b", "Long string, match at the end");
	run_test(++test_count, long_s1, "c", "Long string, no match");
	run_test(++test_count, "b", long_s1, "s2 is long, s1 is short, match 'b'");


	// --- Test from a common example ---
	const char	*str = "This is a sample string";
	const char	*keys = "aeiou";
	run_test(++test_count, str, keys, "Find first vowel"); // Should find 'i' in "is"

	const char	*str2 = "Try not. Do, or do not. There is no try.";
	const char	*keys2 = ".,";
	run_test(++test_count, str2, keys2, "Find first punctuation '.' or ','"); // Should find '.' in "not."

	printf("\nTotal tests: %d\n", test_count);

	return (0);
}
*/