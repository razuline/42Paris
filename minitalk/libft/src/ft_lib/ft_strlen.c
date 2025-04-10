/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erazumov <erazumov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/09 18:14:06 by erazumov          #+#    #+#             */
/*   Updated: 2024/11/26 14:31:31 by erazumov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* The strlen() function calculates the length of the string pointed to by
s, excluding the terminating null byte ('\0').
The strlen() function returns the number of bytes in the string pointed
to by s. */

#include "libft.h"

size_t	ft_strlen(const char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
		i++;
	return (i);
}
/*
void	ft_putchar(char c)
{
	write(1, &c, 1);
}

void	ft_putnbr(int nb)
{
	if (nb == -2147483647)
	{
		ft_putchar('-');
		ft_putchar('2');
		nb = 147483647;
	}
	if (nb < 0)
	{
		ft_putchar('-');
		nb *= -1;
	}
	if (nb > 9)
	{
		ft_putnbr(nb / 10);
		ft_putnbr(nb % 10);
	}
	else
	{
		ft_putchar(nb + 48);
	}
}

int	main(void)
{
	int	len;
	char	s[] = { "Hello, World!" };

	len = ft_strlen(s);
	ft_putnbr(len);
	ft_putchar('\n');
	return (0);
}
*/