/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lcm.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erazumov <erazumov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 19:00:38 by erazumov          #+#    #+#             */
/*   Updated: 2025/05/09 19:09:45 by erazumov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

unsigned int	lcm(unsigned int a, unsigned int b)
{
	unsigned int	hcf;
	unsigned int	swap;
	unsigned int	tmp_a;
	unsigned int	tmp_b;

	if (a == 0 || b == 0)
		return (0);
	tmp_a = a;
	tmp_b = b;
	while (tmp_b != 0)
	{
		swap = tmp_b;
		tmp_b = tmp_a % tmp_b;
		tmp_a = swap;
	}
	hcf = tmp_a;
	return ((a / hcf) * b);
}
/*
#include <stdio.h>

int	main(void)
{
	printf("LCM of 4 and 6: %u\n", lcm(4, 6));      // Output: 12
	printf("LCM of 15 and 20: %u\n", lcm(15, 20));  // Output: 60
	printf("LCM with zero: %u\n", lcm(5, 0));       // Output: 0
	return (0);
}
*/