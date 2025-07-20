/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   powerset_bits.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erazumov <erazumov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/20 14:46:29 by erazumov          #+#    #+#             */
/*   Updated: 2025/07/20 18:02:05 by erazumov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "powerset_bits.h"

int	main(int ac, char **av)
{
	if (ac < 2)
		return (0);
	
	int				k = ac - 2;
	int				target = atoi(av[1]);
	unsigned long	total = 1UL << k;
	int				found = 0;

	unsigned long	mask = 1;
	while (mask < total)
	{
		int			sum = 0;
		int			i = 0;
		while (i < k)
		{
			if (mask & (1UL << i))
				sum += atoi(av[i + 2]);
			++i;
		}
		if (sum == target)
		{
			int		first = 1;
			i = 0;
			while (i < k)
			{
				if (mask & (1UL << i))
				{
					if (!first)
						printf(" ");
					printf("%s", av[i + 2]);
					first = 0;
				}
				++i;
			}
			printf("\n");
			found = 1;
		}
		++mask;
	}
	if (!found)
		printf("\n");
	return (0);
}
