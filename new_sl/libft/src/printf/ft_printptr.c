/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printptr.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erazumov <erazumov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 16:24:18 by razuline          #+#    #+#             */
/*   Updated: 2025/04/10 13:49:06 by erazumov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_ptr_len(unsigned long long n)
{
	int	len;

	len = 0;
	while (n != 0)
	{
		len++;
		n = n / 16;
	}
	return (len);
}

static void	ft_ptr_format(unsigned long long nb)
{
	if (nb >= 16)
	{
		ft_ptr_format(nb / 16);
		ft_ptr_format(nb % 16);
	}
	else
	{
		if (nb <= 9)
			ft_printchar(nb + '0');
		else
			ft_printchar(nb - 10 + 'a');
	}
}

int	ft_printptr(unsigned long long ptr)
{
	int	len;

	len = 0;
	if (ptr == 0)
		len += ft_printstr("(nil)");
	else
	{
		len += ft_printstr("0x");
		ft_ptr_format(ptr);
		len += ft_ptr_len(ptr);
	}
	return (len);
}
/*
int main(void)
{
	int	long long = 123;

	ft_printptr(nbr);
	return (0);
}
*/
