/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erazumov <erazumov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/18 13:47:10 by erazumov          #+#    #+#             */
/*   Updated: 2026/04/18 16:58:07 by erazumov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bsq.h"

/**
 * Reads the first line and validates the characters
 */
int	read_metadata(FILE *fp, t_map *map)
{
	char	*tmp = NULL;
	size_t	len = 0;

	if (fscanf(fp, "%d %c %c %c",
			   &map->height,
			   &map->empty,
			   &map->obs,
			   &map->full) != 4)
		return (0);

	if (map->height <= 0 ||
		map->empty == map->obs ||
		map->empty == map->full ||
		map->obs == map->full)
		return (0);

	getline(&tmp, &len, fp);
	free(tmp);

	return (1);
}

/**
 * Master function to parse the entire map
 */
int	parse_map(FILE *fp, t_map *map)
{
	map->grid = NULL;
	if (!read_metadata(fp, map))
		return (0);

	char		*line = NULL;
	size_t		len = 0;
	ssize_t		read = getline(&line, &len, fp);

	if (read <= 0)
		return (0);

	map->width = (line[read - 1] == '\n') ? (read - 1) : read;

	map->grid = malloc(sizeof(char *) * map->height);
	map->grid[0] = line;

	for (int i = 1; i < map->height; ++i)
	{
		line = NULL;
		len = 0;
		read = getline(&line, &len, fp);

		if (read <= 0 ||
		   ((read - 1 == '\n' ? read - 1 : read) != map->width))
		{
			free(line); return (0);
		}
		map->grid[i] = line;
	}
	return (1);
}

/**
 * Frees all allocated memory for the grid to prevent leaks
 */
void	free_grid(t_map *map)
{
	if (!map->grid)
		return ;

	for (int i = 0; i < map->height; ++i)
		free(map->grid[i]);
	free(map->grid);
}
