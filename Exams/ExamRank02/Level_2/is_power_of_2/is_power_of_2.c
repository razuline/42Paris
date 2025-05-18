/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_power_of_2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erazumov <erazumov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 18:20:29 by erazumov          #+#    #+#             */
/*   Updated: 2025/05/13 21:16:00 by erazumov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	is_power_of_2(unsigned int n)
{
	if (n == 0)
		return (0);
	while (n % 2 == 0)
		n /= 2;
	return (n == 1);
}

/*or*/
/*
int	is_power_of_2(unsigned int n)
{
	if (n == 0)
		return (0);
	return (n & (n - 1)) == 0;
}

#include <stdio.h>

int	main(void)
{
	printf("0: %d (expect 0)\n", is_power_of_2(0));
	printf("1: %d (expect 1)\n", is_power_of_2(1));   // 2^0
	printf("2: %d (expect 1)\n", is_power_of_2(2));
	printf("3: %d (expect 0)\n", is_power_of_2(3));
	printf("4: %d (expect 1)\n", is_power_of_2(4));
	printf("5: %d (expect 0)\n", is_power_of_2(5));
	printf("8: %d (expect 1)\n", is_power_of_2(8));
	printf("1024: %d (expect 1)\n", is_power_of_2(1024));
	printf("1023: %d (expect 0)\n", is_power_of_2(1023));
	
	return (0);
}
*/