/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rush00.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erazumov <erazumov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/04 21:16:41 by erazumov          #+#    #+#             */
/*   Updated: 2025/08/04 22:26:52 by erazumov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_putchar.c"
#include <limits.h>

void	rush(int x, int y)
{
	int		ligne;
	int		col;

	if (!(x <= 0 || x >= INT_MAX) && !(y <= 0 || y >= INT_MAX))
	{
		ligne = 1;
		while (ligne <= y)
		{
			col = 1;
			while (col <= x)
			{
				if ((ligne == 1 || ligne == y) && (col == 1 || col == x))
					ft_putchar('o');
				else if (ligne == 1 || ligne == y)
					ft_putchar('-');
				else if (col == 1 || col == x)
					ft_putchar('|');
				else
					ft_putchar(' ');
				col++;
			}
			ft_putchar('\n');
			ligne++;
		}
	}
}
