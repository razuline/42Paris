/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erazumov <erazumov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 18:43:15 by erazumov          #+#    #+#             */
/*   Updated: 2024/11/26 15:17:13 by erazumov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* Outputs the integer ’n’ to the given file descriptor. External functions:
write. Returns nothing. */

#include "libft.h"

void	ft_putnbr_fd(int nb, int fd)
{
	if (nb == -2147483648)
	{
		ft_putchar_fd('-', fd);
		ft_putchar_fd('2', fd);
		nb = 147483648;
	}
	if (nb < 0)
	{
		ft_putchar_fd('-', fd);
		nb *= -1;
	}
	if (nb > 9)
	{
		ft_putnbr_fd(nb / 10, fd);
		ft_putnbr_fd(nb % 10, fd);
	}
	else
	{
		ft_putchar_fd(nb + '0', fd);
	}
}
/*
int	main(void)
{
	int	res;

	res = -2147483648;
	ft_putnbr_fd(res, 2);
	ft_putchar_fd('\n', 2);
	return (0);
}
*/