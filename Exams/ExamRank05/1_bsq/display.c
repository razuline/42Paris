/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erazumov <erazumov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/18 16:26:23 by erazumov          #+#    #+#             */
/*   Updated: 2026/04/18 16:28:38 by erazumov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bsq.h"

/**
 * Fills the found square with the 'full' character and prints the map
 * The square is defined by its bottom-right corner (row, col) and its size
 */
void	fill_and_print(t_map *map, int size, int row, int col)
{
	int	i;
	int	j;

	// 1. Fill the square area in the grid
	// Start from the bottom-right corner and go back up and left
	for (i = row - size + 1; i <= row; i++)
	{
		for (j = col - size + 1; j <= col; j++)
		{
			map->grid[i][j] = map->full;
		}
	}

	// 2. Print each line of the grid to stdout
	// Since getline kept the '\n' at the end of each line, fputs works perfectly
	for (i = 0; i < map->height; i++)
	{
		fputs(map->grid[i], stdout);
	}
}
