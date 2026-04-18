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
	int	min;

	min = a;
	if (b < min)
		min = b;
	if (c < min)
		min = c;
	return (min);
}

/**
 * Frees the memory of the integer DP table
 */
void	free_dp(int **dp, int height)
{
	for (int i = 0; i < height; i++)
		free(dp[i]);
	free(dp);
}

/**
 * Dynamic Programming algorithm to find the biggest square
 */
void	solve_bsq(t_map *map)
{
	int	**dp;
	int	max_size = 0;
	int	max_x = 0;
	int	max_y = 0;

	// 1. Allocate DP table (array of int)
	dp = malloc(sizeof(int) * map->height);
	for (int i = 0; i < map->height; i++)
	{
		dp[i] = malloc(sizeof(int) * map->width);
		for (int j = 0; j < map->width; j++)
		{
			// 2. Base case: if obstacle, value is 0
			if (map->grid[i][j] == map->obs)
				dp[i][j] = 0;
			// 3. Base case: 1st row or 1st column
			else if (i == 0 || j == 0)
				dp[i][j] = 1;
			// 4. DP step: look at 3 neighbors
			else
				dp[i][j] = min_of_three(dp[i-1][j], dp[i][j-1], dp[i-1][j-1]) + 1;

			// 5. Track the global max
			if (dp[i][j] > max_size)
			{
				max_size = dp[i][j];
				max_y = i;
				max_x = j;
			}
		}
	}
	// 6. Draw and show results
	fill_and_print(map, max_size, max_y, max_x);

	// 7. Clean up the calculation table
	free_dp(dp, map->height);
}
