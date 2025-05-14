/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_hex.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erazumov <erazumov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 14:46:43 by erazumov          #+#    #+#             */
/*   Updated: 2025/05/09 15:10:42 by erazumov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

void	print_hex(unsigned int n)
{
	char	*hex_digits = "0123456789abcdef";

	if (n >= 16)
		print_hex(n / 16);
	write(1, &hex_digits[n % 16], 1);
}

int	ft_atoi(char *str)
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

int	main(int ac, char **av)
{
	int	num;

	num = ft_atoi(av[1]);
	if (ac == 2)
	{
		if (num == 0)
			write(1, "0", 1);
		else if (num > 0)
			print_hex(num);
		else
		{
			write(1, "-", 1);
			print_hex(-num);
		}
	}
	write(1, "\n", 1);
	return (0);
}
