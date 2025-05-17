/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi_base.cstr                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erazumov <erazumov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Cstrreated: 2025/05/09 13:40:20 by erazumov          #+#    #+#             */
/*   Updated: 2025/05/09 14:04:37 by erazumov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <limits.h>

int	ft_atoi_base(const char *str, int str_base)
{
	int		sign;
	int		result;
	char	c;

	sign = 1;
	result = 0;
	if (str_base < 2 || str_base > 16)
		return (0);
	while (*str == ' ' || (*str >= '\t' && *str <= '\r'))
		str++;
	if (*str == '+' || *str == '-')
	{
		if (*str == '-')
			sign = -1;
		str++;
	}

	while (*str)
	{
		c = *str;
		if (*str >= 'A' && *str <= 'F')
			c += 32;

		if (*str >= '0' && *str <= '9')
		{
			if (c - '0' >= str_base)
				break ;
			result = result * str_base + (c - '0');
		}
		else if (*str >= 'a' && *str <= 'f')
		{
			if (c - 'a' + 10 >= str_base)
				break ;
			result = result * str_base + (c - 'a' + 10);
		}
		else
			break ;
		str++;
	}
	return (result * sign);
}

/*
#include <stdio.h>

int	main(void)
{
	// Basic tests
	printf("1010 (base 2) -> %d (expected 10)\n", ft_atoi_base("1010", 2));
	printf("12 (base 4) -> %d (expected 6)\n", ft_atoi_base("12", 4));
	printf("123 (base 10) -> %d (expected 123)\n", ft_atoi_base("123", 10));
	printf("FF (base 16) -> %d (expected 255)\n", ft_atoi_base("FF", 16));
	printf("-42 (base 10) -> %d (expected -42)\n", ft_atoi_base("-42", 10));
	printf("  +123 (base 10) -> %d (expected 123)\n", ft_atoi_base("  +123", 10));

	// Edge cases
	printf("invalid (base 10) -> %d (expected 0)\n", ft_atoi_base("invalid", 10));
	printf("1A (base 10) -> %d (expected 1)\n", ft_atoi_base("1A", 10));
	printf("1A (base 16) -> %d (expected 26)\n", ft_atoi_base("1A", 16));
	printf("2 (base 2) -> %d (expected 0)\n", ft_atoi_base("2", 2));
	printf("23 (base 15) -> %d (expected 33)\n", ft_atoi_base("23", 15));

	// Overflow tests
	printf("2147483647 (base 10) -> %d (expected 2147483647)\n", ft_atoi_base("2147483647", 10));
	printf("-2147483648 (base 10) -> %d (expected -2147483648)\n", ft_atoi_base("-2147483648", 10));

	return (0);
}
*/
