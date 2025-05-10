/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erazumov <erazumov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/10 11:59:13 by erazumov          #+#    #+#             */
/*   Updated: 2025/05/10 11:59:14 by erazumov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

int		get_num_len(int n)
{
	int	len;

	len = 0;
	if (n <= 0)
		len++;
	while (n != 0)
	{
		len++;
		n /= 10;
	}
	return (len);
}

char	*ft_itoa(int nbr)
{
	int		len;
	long	num;
	char	*result;

	num = nbr;
	len = get_num_len(num);

	result = (char*)malloc(sizeof(char) * (len + 1));
	if (!result)
		return (NULL);

	result[len--] = '\0';

	if (num == 0)
		result[0] = '0';
	if (num < 0)
	{
		result[0] = '-';
		num = -num;
	}
	while (num > 0)
	{
		result[len--] = (num % 10) + '0';
		num /= 10;
	}
	return (result);
}

#include <stdio.h>

int	main(void)
{
	printf("%s\n", ft_itoa(0));           // "0"
	printf("%s\n", ft_itoa(123));         // "123"
	printf("%s\n", ft_itoa(-456));        // "-456"
	printf("%s\n", ft_itoa(2147483647));  // "2147483647"
	printf("%s\n", ft_itoa(-2147483648)); // "-2147483648"
}
