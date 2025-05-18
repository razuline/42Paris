/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_prime_sum.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erazumov <erazumov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 15:29:35 by erazumov          #+#    #+#             */
/*   Updated: 2025/05/17 13:36:14 by erazumov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

// Recursive number printing
void	ft_putnbr(int nb)
{
	char	c;

	if (nb >= 10)
		ft_putnbr(nb / 10);
	c = nb % 10 + '0';
	write(1, &c, 1);
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

// Recursive prime check
int	is_prime(int num, int divisor)
{
	if (num <= 1)
		return (0);
	if (divisor * divisor > num)
		return (1);
	if (num % divisor == 0)
		return (0);
	return (is_prime(num, divisor + 1));
}

// Recursive prime sum
int	add_prime_sum(int curr, int limit)
{
	int	prime_flag;
	int	curr_value;

	if (curr > limit) // Base case
		return (0);
	prime_flag = is_prime(curr, 2);

	if (prime_flag)
		curr_value = curr;
	else
		curr_value = 0;
	return (curr_value + add_prime_sum(curr + 1, limit));
}

int	main(int ac, char **av)
{
	int	num;
	int	sum;

	if (ac != 2)
	{
		write(1, "0\n", 2);
		return (0);
	}
	num = ft_atoi(av[1]);
	if (num < 1)
	{
		write(1, "0\n", 2);
		return (0);
	}
	sum = add_prime_sum(2, num);
	ft_putnbr(sum);
	write(1, "\n", 1);
	return (0);
}
