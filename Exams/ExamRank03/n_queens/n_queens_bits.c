/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   n_queens_bits.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erazumov <erazumov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/20 18:03:41 by erazumov          #+#    #+#             */
/*   Updated: 2025/07/20 18:33:32 by erazumov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "n_queens_bits.h"

typedef unsigned long	mask;

void	disp(int *q, int n)
{
	int	i;

	i = 0;
	while (i < n)
	{
		printf("%d", q[i]);
		if (i < n - 1)
			printf(" ");
		i++;
	}
	printf("\n");
}

void	bt(int *q, int col, int n, mask rows, mask d1, mask d2)
{
	int	r;

	if (col == n)
	{
		disp(q, n);
		return ;
	}
	r = 0;
	while (r < n)
	{
		mask	rm = 1UL << r;
		mask	d1m = 1UL << (col + r);
		mask	d2m = 1UL << (r - col + n);
		if (!(rows & rm) && !(d1 & d1m) && !(d2 & d2m))
		{
			q[col] = r;
			bt(q, col + 1, n, rows | rm, d1 | d1m, d2 | d2m);
		}
		r++;
	}
}

int	main(int ac, char **av)
{
	int	n;
	int	q[32];

	if (ac != 2)
		return (0);
	n = atoi(av[1]);
	bt(q, 0, n, 0, 0, 0);
	return (0);
}
