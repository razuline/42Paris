/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erazumov <erazumov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 17:55:58 by erazumov          #+#    #+#             */
/*   Updated: 2025/05/13 18:06:46 by erazumov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_atoi(const char *str)
{
	int	sign;
	int	result;

	sign = 1;
	result = 0;
	while (*str == ' ' || (*str >= '\t' && *str <= '\r'))
		str++;
	if (*str == '+' || *str == '-')
	{
		if (*str == '-')
			sign = -1;
		str++;
	}
	while (*str >= '0' && *str <= '9')
	{
		result = result * 10 + (*str - '0');
		str++;
	}
	return (result * sign);
}

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

// Helper function to run tests and print results
void	run_test(int test_num, const char *input_str, const char *description) {
	int	my_result = ft_atoi(input_str);
	int	std_result = atoi(input_str); // Using standard atoi for comparison

	printf("Test %d: Input = \"%s\"\n", test_num, input_str);
	printf("Description: %s\n", description);
	printf("  ft_atoi: %d\n", my_result);
	printf("  atoi   : %d\n", std_result);

	if (my_result == std_result) {
		printf("  Result: \033[32mOK\033[0m\n"); // Green color for OK
	} else {
		// For overflow/underflow cases, atoi's behavior is undefined by C standard.
		// Some systems might return INT_MAX/INT_MIN, others might wrap.
		// We'll flag if they are different but acknowledge this potential discrepancy.
		if ((input_str[0] == '-' && (long long)std_result == LLONG_MIN && (long long)my_result != LLONG_MIN) ||
			(input_str[0] != '-' && (long long)std_result == LLONG_MAX && (long long)my_result != LLONG_MAX)) {
			 printf("  Result: \033[33mDIFFERENT (Potential Overflow/Underflow behavior difference with standard atoi)\033[0m\n");
		} else {
			printf("  Result: \033[31mFAIL\033[0m\n"); // Red color for FAIL
		}
	}
	printf("----------------------------------------\n");
}

int	main(void)
{
	int	test_count = 0;

	// --- Basic positive numbers ---
	run_test(++test_count, "42", "Simple positive");
	run_test(++test_count, "0", "Zero");
	run_test(++test_count, "12345", "Positive number");
	run_test(++test_count, "+42", "Positive with plus sign");
	run_test(++test_count, "++42", "Double plus sign (atoi behavior: 0)");
	run_test(++test_count, "+", "Only plus sign (atoi behavior: 0)");


	// --- Basic negative numbers ---
	run_test(++test_count, "-42", "Simple negative");
	run_test(++test_count, "-0", "Negative zero");
	run_test(++test_count, "-12345", "Negative number");
	run_test(++test_count, "--42", "Double minus sign (atoi behavior: 0)");
	run_test(++test_count, "-", "Only minus sign (atoi behavior: 0)");

	// --- Numbers with leading/trailing whitespace ---
	run_test(++test_count, "   42", "Leading spaces");
	run_test(++test_count, "\t\n\v\f\r 42", "Leading various whitespaces");
	run_test(++test_count, "42   ", "Trailing spaces (ignored after number)");
	run_test(++test_count, "  -42", "Leading spaces, negative");
	run_test(++test_count, "  +42", "Leading spaces, positive with plus");

	// --- Numbers with non-digit characters ---
	run_test(++test_count, "42abc", "Number followed by letters");
	run_test(++test_count, "42 abc", "Number followed by space and letters");
	run_test(++test_count, "-42abc", "Negative number followed by letters");
	run_test(++test_count, "  42abc", "Spaces, number, letters");
	run_test(++test_count, "  -42abc", "Spaces, negative number, letters");
	run_test(++test_count, "  +42abc", "Spaces, positive sign, number, letters");
	run_test(++test_count, "abc42", "Letters before number (atoi behavior: 0)");
	run_test(++test_count, "a-42", "Letter before negative number (atoi behavior: 0)");

	// --- Edge cases ---
	run_test(++test_count, "", "Empty string (atoi behavior: 0)");
	run_test(++test_count, "  ", "Only spaces (atoi behavior: 0)");
	run_test(++test_count, "\t", "Only tab (atoi behavior: 0)");
	run_test(++test_count, "+-42", "Plus minus (atoi behavior: 0)");
	run_test(++test_count, "-+42", "Minus plus (atoi behavior: 0)");
	run_test(++test_count, "00042", "Leading zeros");
	run_test(++test_count, "-00042", "Negative with leading zeros");

	printf("\nTotal tests: %d\n", test_count);

	return (0);
}
