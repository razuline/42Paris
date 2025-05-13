/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcspn.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erazumov <erazumov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 15:31:58 by erazumov          #+#    #+#             */
/*   Updated: 2025/05/13 17:29:14 by erazumov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

size_t	ft_strcspn(const char *s, const char *reject)
{
	int		found;
	size_t	count;
	const char	*s_ptr;
	const char	*reject_ptr;

	count = 0;
	s_ptr = s;
	while (*s_ptr != '\0')
	{
		found = 0;
		reject_ptr = reject;
		while (*reject_ptr != '\0')
		{
			if (*s_ptr == *reject_ptr)
			{
				found = 1;
				break ;
			}
			reject_ptr++;
		}
		if (found == 1)
			return (count);
		else
			count++;
		s_ptr++;
	}
	return (count);
}
/*
#include <stdio.h>
#include <string.h>
#include <stddef.h>

// Helper function to run tests and print results
void	run_test(int test_num, const char *s, const char *reject, const char *description) {
	size_t	my_result = ft_strcspn(s, reject);
	size_t	std_result = strcspn(s, reject); // Using standard strcspn for comparison

	printf("Test %d: s = \"%s\", reject = \"%s\"\n", test_num, s, reject);
	printf("Description: %s\n", description);
	printf("  ft_strcspn: %zu\n", my_result);
	printf("  strcspn   : %zu\n", std_result);

	if (my_result == std_result) {
		printf("  Result: \033[32mOK\033[0m\n"); // Green color for OK
	} else {
		printf("  Result: \033[31mFAIL\033[0m\n"); // Red color for FAIL
	}
	printf("----------------------------------------\n");
}

int	main(void)
{
	int	test_count = 0;

	// --- Basic test cases ---
	run_test(++test_count, "aabbcde", "cx", "Basic case, 'c' is in reject"); // Expect 2 (aa)
	run_test(++test_count, "hello world", " ", "Reject set contains space"); // Expect 5 (hello)
	run_test(++test_count, "hello world", "o", "Reject set contains 'o'"); // Expect 4 (hell)
	run_test(++test_count, "tripouille", "p", "Reject 'p'"); // Expect 2 (tr)
	run_test(++test_count, "tripouille", "z", "Reject 'z' (not in s)"); // Expect 10 (length of "tripouille")
	run_test(++test_count, "abc", "xyz", "No common characters"); // Expect 3 (length of "abc")

	// --- Edge cases (empty strings) ---
	run_test(++test_count, "", "abc", "s is an empty string"); // Expect 0
	run_test(++test_count, "abc", "", "reject is an empty string"); // Expect 3 (length of "abc")
	run_test(++test_count, "", "", "Both strings are empty"); // Expect 0

	// --- More complex cases ---
	run_test(++test_count, "banana", "na", "Reject 'n' or 'a'"); // Expect 1 ('b')
	run_test(++test_count, "banana", "x", "Reject 'x' (not in s)"); // Expect 6
	run_test(++test_count, "test", "es", "Reject 'e' or 's'"); // Expect 1 ('t')
	run_test(++test_count, "abcdef", "fedcba", "All chars of s are in reject"); // Expect 0
	run_test(++test_count, "abcdef", "x", "Reject 'x'"); // Expect 6
	run_test(++test_count, "aaabbbccc", "b", "Reject 'b'"); // Expect 3 ("aaa")
	run_test(++test_count, "aaabbbccc", "c", "Reject 'c'"); // Expect 6 ("aaabbb")
	run_test(++test_count, "aaabbbccc", "d", "Reject 'd' (not in s)"); // Expect 9
	run_test(++test_count, "abC", "C", "Case sensitivity: 'C' in reject"); // Expect 2 ("ab")
	run_test(++test_count, "abC", "c", "Case sensitivity: 'c' in reject (not 'C')"); // Expect 3 ("abC")

	// --- Examples from man strcspn (or similar logic) ---
	// strcspn("abcde01987", "0123456789") should return 5 (length of "abcde")
	run_test(++test_count, "abcde01987", "0123456789", "Man page like example 1"); // Expect 5
	// strcspn("01987abcde", "0123456789") should return 0
	run_test(++test_count, "01987abcde", "0123456789", "Man page like example 2"); // Expect 0
	run_test(++test_count, "hello", "l", "Reject 'l'"); // Expect 2 ("he")
	run_test(++test_count, "hello", "lo", "Reject 'l' or 'o'"); // Expect 2 ("he")

	// --- Test with a long string ---
	char	long_s[1001];
	for (int i = 0; i < 500; ++i) { long_s[i] = 'x'; }
	for (int i = 500; i < 1000; ++i) { long_s[i] = 'y'; }
	long_s[1000] = '\0';
	run_test(++test_count, long_s, "y", "Long string, reject 'y'"); // Expect 500 (the 'x's)

	char	long_s2[1001];
	for (int i = 0; i < 1000; ++i) { long_s2[i] = 'z'; }
	long_s2[1000] = '\0';
	run_test(++test_count, long_s2, "a", "Long string of 'z', reject 'a'"); // Expect 1000

	char	long_s3[1001];
	for (int i = 0; i < 1000; ++i) { long_s3[i] = 'z'; }
	long_s3[1000] = '\0';
	run_test(++test_count, long_s3, "z", "Long string of 'z', reject 'z'"); // Expect 0

	printf("\nTotal tests: %d\n", test_count);

	return (0);
}
*/