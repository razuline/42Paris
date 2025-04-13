/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printhex.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erazumov <erazumov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/29 15:44:02 by erazumov          #+#    #+#             */
/*   Updated: 2025/04/10 13:49:06 by erazumov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_hex_len(unsigned int n)
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

static void	ft_hex_format(unsigned int nb, const char format)
{
	if (nb >= 16)
	{
		ft_hex_format(nb / 16, format);
		ft_hex_format(nb % 16, format);
	}
	else
	{
		if (nb <= 9)
			ft_printchar(nb + '0');
		else
		{
			if (format == 'x')
				ft_printchar(nb - 10 + 'a');
			if (format == 'X')
				ft_printchar(nb - 10 + 'A');
		}
	}
}

int	ft_printhex(unsigned int nbr, const char format)
{
	if (nbr == 0)
		return (ft_printchar('0'));
	else
		ft_hex_format(nbr, format);
	return (ft_hex_len(nbr));
}

/*
int main(void)
{
	int	nbr = 123;
	char	format = 'x';

	ft_printhex(nbr, format);
	return (0);
}
*/
