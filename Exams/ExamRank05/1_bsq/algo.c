/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   algo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erazumov <erazumov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/18 16:03:19 by erazumov          #+#    #+#             */
/*   Updated: 2026/04/18 16:38:44 by erazumov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bsq.h"

/**
 * Helper function to find the minimum of three integers
 */
int	min_of_three(int a, int b, int c)
{
	int	min = a;

	if (b < min)
		min = b;
	if (c < min)
		min = c;
	return (min);
}

/**
 * Dynamic Programming algorithm to find the biggest square
 */
void	solve_bsq(t_map *map)
{
	int	*dp = calloc(map->width, sizeof(int));
	int	prev_diag;
	int	tmp;
	int	max_size = 0;
	int	max_x = 0;
	int	max_y = 0;

	if (!dp)
		return ;

	for (int i = 0; i < map->height; ++i)
	{
		prev_diag = 0;
		for (int j = 0; j < map->width; ++j)
		{
			tmp = dp[j];
			if (map->grid[i][j] == map->obs)
				dp[j] = 0;
			else
			{
				int	left = (j > 0) ? dp[j - 1] : 0;

				dp[j] = min_of_three(left, dp[j], prev_diag) + 1;

				if (dp[j] > max_size)
				{
					max_size = dp[j];
					max_x = j;
					max_y = i;
				}
			}
			prev_diag = tmp;
		}
	}
	fill_and_print(map, max_size, max_y, max_x);
	free(dp);
}
