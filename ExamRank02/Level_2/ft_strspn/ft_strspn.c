/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strspn.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erazumov <erazumov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 15:30:55 by erazumov          #+#    #+#             */
/*   Updated: 2025/05/13 21:15:30 by erazumov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

size_t	ft_strspn(const char *s, const char *accept)
{
	int			found;
	size_t		count;
	const char	*s_ptr;
	const char	*accept_ptr;

	count = 0;
	s_ptr = s;

	while (*s_ptr != '\0')
	{
		found = 0;
		accept_ptr = accept;
		while (*accept_ptr != '\0')
		{
			if (*s_ptr == *accept_ptr)
			{
				found = 1;
				break ;
			}
			accept_ptr++;
		}
		if (found == 1)
			count++;
		else
			return (count);
		s_ptr++;
	}
	return (count);
}

/*
#include <stdio.h>
#include <string.h>
#include <stddef.h>

// Helper function to run tests and print results
void	run_test(int test_num, const char *s, const char *accept, const char *description) {
	size_t	my_result = ft_strspn(s, accept);
	size_t	std_result = strspn(s, accept); // Using standard strspn for comparison

	printf("Test %d: s = \"%s\", accept = \"%s\"\n", test_num, s, accept);
	printf("Description: %s\n", description);
	printf("  ft_strspn: %zu\n", my_result);
	printf("  strspn   : %zu\n", std_result);

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
	run_test(++test_count, "aabbcde", "ab", "Basic case");
	run_test(++test_count, "cdeaabb", "ab", "No match at the beginning");
	run_test(++test_count, "abc", "abc", "All characters match");
	run_test(++test_count, "abc", "abcdef", "accept is a superset");
	run_test(++test_count, "tripouille", "t", "Single char in accept, match at start");
	run_test(++test_count, "tripouille", "tri", "Multiple chars in accept, match at start");
	run_test(++test_count, "tripouille", "z", "No matches");
	run_test(++test_count, "tripouille", "tripouille", "Full match");

	// --- Edge cases (empty strings) ---
	run_test(++test_count, "", "abc", "s is an empty string");
	run_test(++test_count, "abc", "", "accept is an empty string");
	run_test(++test_count, "", "", "Both strings are empty");

	// --- More complex cases ---
	run_test(++test_count, "banana", "ban", "Chars in accept repeat, s matches fully");
	run_test(++test_count, "banaXna", "ban", "Match interrupted by 'X'");
	run_test(++test_count, "test", "xyz", "No common characters");
	run_test(++test_count, "hello world", "h", "Only first char of s is in accept");
	run_test(++test_count, "hello world", "helo", "Several chars from accept consecutively in s"); // h,e,l,l,o -> 5
	run_test(++test_count, "hello world", " ", "Space in accept, but not at start of s"); // -> 0
	run_test(++test_count, "  hello world", " ", "Spaces at start of s, space in accept"); // -> 2
	run_test(++test_count, "abc123abc", "abc", "Match first segment");
	run_test(++test_count, "123abc123", "123", "Match numbers");
	run_test(++test_count, "ababab", "b", "s starts with 'a', accept contains 'b'"); // -> 0
	run_test(++test_count, "bbbaaa", "b", "s starts with 'b', accept contains 'b'"); // -> 3
	run_test(++test_count, "abcdef", "fedcba", "All chars of s are in accept (order in accept doesn't matter)"); // -> 6
	run_test(++test_count, "abcdef", "axbyczd", "Accept chars mixed with others"); // a,b,c -> 3
	run_test(++test_count, "aaabbbccc", "abc", "All chars of s are in accept"); // -> 9
	run_test(++test_count, "aaabbbccc", "acb", "All chars of s are in accept (order in accept doesn't matter)"); // -> 9
	run_test(++test_count, "abC", "abc", "Case sensitivity: 'C' not in 'abc'"); // -> 2

	// --- Examples from man strspn ---
	run_test(++test_count, "abcde01987", "abc", "Example from man 1"); // Expect 3
	run_test(++test_count, "01987abcde", "0123456789", "Example from man 2"); // Expect 5

	// --- Test with a long string ---
	char	long_s[1001];
	for (int i = 0; i < 500; ++i) { long_s[i] = 'x'; }
	for (int i = 500; i < 1000; ++i) { long_s[i] = 'y'; }
	long_s[1000] = '\0';
	run_test(++test_count, long_s, "x", "Long string, accept 'x'"); // Expect 500

	char	long_s2[1001];
	for (int i = 0; i < 1000; ++i) { long_s2[i] = 'z'; }
	long_s2[1000] = '\0';
	run_test(++test_count, long_s2, "z", "Long string of 'z', accept 'z'"); // Expect 1000

	printf("\nTotal tests: %d\n", test_count);

	return (0);
}
*/