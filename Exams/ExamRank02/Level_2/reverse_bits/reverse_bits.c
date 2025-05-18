/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reverse_bits.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erazumov <erazumov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 21:04:06 by erazumov          #+#    #+#             */
/*   Updated: 2025/05/13 21:16:18 by erazumov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

unsigned char	reverse_bits(unsigned char octet)
{
	int				i;
	unsigned char	result;

	i = 8;
	result = 0;
	while (i--)
	{
		result = (result << 1) | (octet & 1);
		octet >>= 1;
	}
	return (result);
}

/*
#include <stdio.h>

int	main(void)
{
	printf("%u\n", reverse_bits(1));     // 128
	printf("%u\n", reverse_bits(2));     // 64
	printf("%u\n", reverse_bits(65));    // 130 (01000001 -> 10000010)
	printf("%u\n", reverse_bits(255));   // 255
	printf("%u\n", reverse_bits(0));     // 0
	return (0);
}
*/