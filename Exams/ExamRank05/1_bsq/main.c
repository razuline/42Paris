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
 * Fills the found square with the 'full' character and prints the map
 * The square is defined by its bottom-right corner (row, col) and its size
 */
void	fill_and_print(t_map *map, int size, int row, int col)
{
	for (int i = row - size + 1; i <= row; i++)
	{
		for (int j = col - size + 1; j <= col; j++)
			map->grid[i][j] = map->full;
	}
	for (int i = 0; i < map->height; i++)
		fputs(map->grid[i], stdout);
}

/**
 * Core logic for processing a single map source
 */
void	process_map(FILE *fp)
{
	t_map	map;

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
