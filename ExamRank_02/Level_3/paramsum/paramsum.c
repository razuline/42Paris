/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   paramsum.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erazumov <erazumov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 18:21:58 by erazumov          #+#    #+#             */
/*   Updated: 2025/05/09 18:29:38 by erazumov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

void	ft_putchar(char c)
{
	write(1, &c, 1);
}

void	ft_putnbr(int nb)
{
	if (nb >= 10)
		ft_putnbr(nb / 10);
	ft_putchar((nb % 10) + '0');
}

int	main(int ac, char **av)
{
	(void)av;

	if (ac == 1)
		write(1, "0\n", 2);
	else
	{
		ft_putnbr(ac - 1);
		write(1, "\n", 1);
	}
	return (0);
}
