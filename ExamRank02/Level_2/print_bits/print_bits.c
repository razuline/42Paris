/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_bits.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erazumov <erazumov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 20:50:45 by erazumov          #+#    #+#             */
/*   Updated: 2025/05/13 21:14:56 by erazumov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

void	print_bits(unsigned char octet)
{
	unsigned char	mask;

	mask = 128;  // 10000000 in binary
	while (mask)
	{
		if (octet & mask)
			write(1, "1", 1);
		else
			write(1, "0", 1);
		mask >>= 1;
	}
}

/*
int	main(void)
{
	// Test cases with labels
	write(1, "2:    ", 6);
	print_bits(2);    // Should print "00000010"
	write(1, "\n", 1);
	
	write(1, "5:    ", 6);
	print_bits(5);    // Should print "00000101" 
	write(1, "\n", 1);
	
	write(1, "42:   ", 6);
	print_bits(42);   // Should print "00101010"
	write(1, "\n", 1);
	
	write(1, "255:  ", 6);
	print_bits(255);  // Should print "11111111"
	write(1, "\n", 1);
	
	write(1, "0:    ", 6);
	print_bits(0);    // Should print "00000000"
	write(1, "\n", 1);
	
	return (0);
}
*/