/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   swap_bits.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erazumov <erazumov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 21:11:31 by erazumov          #+#    #+#             */
/*   Updated: 2025/05/13 21:16:25 by erazumov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

unsigned char	swap_bits(unsigned char octet)
{
	return (octet << 4) | (octet >> 4);
}

/*
#include <stdio.h>

int	main(void)
{
	printf("%d\n", swap_bits(65));   // 01000001 → 00010100 (20)
	printf("%d\n", swap_bits(20));   // 00010100 → 01000001 (65)
	printf("%d\n", swap_bits(255));  // 11111111 → 11111111 (255)
	printf("%d\n", swap_bits(0));    // 00000000 → 00000000 (0)
	printf("%d\n", swap_bits(170));  // 10101010 → 10101010 (170)
	return (0);
}
*/