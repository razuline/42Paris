/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_swap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erazumov <erazumov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/10 17:43:54 by erazumov          #+#    #+#             */
/*   Updated: 2025/05/11 11:21:33 by erazumov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

void	ft_swap(int *a, int *b)
{
	int	tmp;

	if (!a || !b || a == b)
		return ;

	tmp = *a;
	*a = *b;
	*b = tmp;
}
/*
#include <stdio.h>
#include <limits.h>

void	run_test(int a, int b)
{
	int	original_a = a;
	int	original_b = b;
	
	printf("Before swap: a = %d, b = %d\n", a, b);
	ft_swap(&a, &b);
	printf("After swap:  a = %d, b = %d  ", a, b);
	
	if (a == original_b && b == original_a)
		printf("\033[0;32mOK\033[0m\n\n");
	else
		printf("\033[0;31mFAIL\033[0m\n\n");
}

int	main(void)
{
	// Test 1: Positive numbers
	run_test(5, 10);
	
	// Test 2: Negative numbers
	run_test(-3, -7);
	
	// Test 3: Positive and negative numbers
	run_test(15, -20);
	
	// Test 4: Zero
	run_test(0, 0);
	
	// Test 5: Max int
	run_test(INT_MAX, INT_MIN);
	
	// Test 6: Same numbers
	run_test(100, 100);
	
	return (0);
}
*/