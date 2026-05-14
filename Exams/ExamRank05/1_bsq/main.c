/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erazumov <erazumov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/18 16:00:32 by erazumov          #+#    #+#             */
/*   Updated: 2026/04/18 16:56:25 by erazumov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bsq.h"

/**
 * Fills the identified biggest square and prints the result.
 * @param map  Structure containing map data
 * @param size Side length of the biggest square
 * @param row  Bottom-right Y coordinate
 * @param col  Bottom-right X coordinate
 */
void	fill_and_print(t_map *map, int size, int row, int col)
{
	// Iterate through the square area to replace 'empty' with 'full' chars
	for (int i = row - size + 1; i <= row; i++)
	{
		for (int j = col - size + 1; j <= col; j++)
			map->grid[i][j] = map->full;
	}
	// Print the final grid to standard output line by line
	for (int i = 0; i < map->height; i++)
		fputs(map->grid[i], stdout);
}

/**
 * Handles the execution flow for a single map source.
 * @param fp File pointer (either a file or stdin)
 */
void	process_map(FILE *fp)
{
	t_map	map;

	// Attempt to parse and validate the map metadata and grid
	if (!parse_map(fp, &map))
	{
		write(2, "map error\n", 10);
		return ;
	}
	solve_bsq(&map);
	free_grid(&map);
}

int	main(int ac, char **av)
{
	int		i;
	FILE	*fp;

	if (ac == 1)
		process_map(stdin);
	else
	{
		for (i = 1; i < ac; ++i)
		{
			fp = fopen(av[i], "r");
			if (fp == NULL)
				fprintf(stderr, "map error\n");
			else
			{
				process_map(fp);
				fclose(fp);
			}
			if (i < ac - 1)
				printf("\n");
		}
	}
	return (0);
}
