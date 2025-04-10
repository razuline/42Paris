/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erazumov <erazumov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/15 13:49:22 by erazumov          #+#    #+#             */
/*   Updated: 2025/04/10 13:49:06 by erazumov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* Allocates (with malloc(3)) and returns a string representing the integer
received as an argument. Negative numbers must be handled.
The string representing the integer. NULL if the allocation fails. */

#include "libft.h"

static int	ft_intlen(int nb)
{
	int	len;

	if (nb == -2147483648)
	{
		len = 11;
		return (len);
	}
	len = 0;
	if (nb < 0)
	{
		nb *= -1;
		len++;
	}
	while (nb > 9)
	{
		nb /= 10;
		len++;
	}
	if (nb < 10)
		len++;
	return (len);
}

char	*ft_itoa(int num)
{
	int		len;
	char	*str;
	long	number;

	len = ft_intlen(num);
	str = (char *)malloc(sizeof(char) * (len + 1));
	if (!str)
		return (NULL);
	str[len] = '\0';
	number = num;
	if (number == 0)
		str[0] = '0';
	if (number < 0)
	{
		str[0] = '-';
		number = -number;
	}
	while (number != 0)
	{
		str[len - 1] = (number % 10) + '0';
		number /= 10;
		len--;
	}
	return (str);
}
/*
#include <stdio.h>

int	main(void)
{
	int		i;
	char	*res;

	i = 10;
	printf("%d\n", ft_intlen(i));
	res = ft_itoa(i);
	printf("%s\n", res);
	return(0);
}
*/
