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
	// Read height and characters
	if (fscanf(fp, "%d %c %c %c", &map->height, &map->empty,
					&map->obs, &map->full) != 4)
	{
		return (0);
	}

	if (map->empty < 32 ||
		map->empty > 126 ||
		map->obs < 32 ||
		map->obs > 126 ||
		map->full < 32 ||
		map->full > 126)
	{
		return (0);
	}

	// Basic validation: positive height and unique characters
	if (map->height <= 0 ||
		map->empty == map->obs ||
		map->empty == map->full ||
		map->obs == map->full)
	{
		return (0);
	}

	// Consume the remaining '\n' after the header
	char	*tmp_line = NULL;
	size_t	len = 0;
	getline(&tmp_line, &len, fp);
	free(tmp_line);

	return (1);
}

/**
 * Reads the first grid line to determine width and allocates memory
 */
int	init_grid(FILE *fp, t_map *map)
{
	char	*line = NULL;
	size_t	len = 0;
	ssize_t	read;

	// 1. Actually read the line to find the width
	read = getline(&line, &len, fp);
	if (read <= 0)
		return (0); // map error

	// Set the width (ignoring the newline char)
	map->width = (line[read - 1] == '\n') ? (read - 1) : read;

	for (int j = 0; j < map->width; j++)
	{
		if (line[j] != map->empty && line[j] != map->obs)
		{
			free(line);
			return (0);
		}
	}

	// 3. Prepare memory for the whole map
	map->grid = malloc(sizeof(char *) * map->height);
	if (!map->grid)
	{
		free(line);
		return (0);
	}

	// 4. Save this line as the very first row
	map->grid[0] = line;
	return (1);
}

/**
 * Reads all remaining lines and validates their length
 */
int	load_lines(FILE *fp, t_map *map)
{
	char	*line;
	size_t	len;
	ssize_t	read;

	for (int i = 1; i < map->height; i++)
	{
		line = NULL;
		len = 0;
		read = getline(&line, &len, fp);

		// Check if line length matches map->width
		int	curr_width = (read > 0 && line[read - 1] == '\n') ? (read - 1) : read;

		if (read <= 0 || curr_width != map->width)
		{
			free(line);
			return (0);
		}
		for (int j = 0; j < map->width; j++)
		{
			if (line[j] != map->empty && line[j] != map->obs)
			{
				free(line);
				return (0);
			}
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
	int	i;

	// 1. Check if the grid actually exists
	if (map->grid == NULL)
		return ;

	// 2. Free each individual line
	for (i = 0; i < map->height; i++)
	{
		if (map->grid[i] != NULL)
		{
			free(map->grid[i]);
			map->grid[i] = NULL; // Good practice: prevent dangling pointers
		}
	}

	// 3. Free the array of pointers itself
	free(map->grid);
	map->grid = NULL;
}

/**
 * Master function to parse the entire map
 */
int	parse_map(FILE *fp, t_map *map)
{
	// Initialise grid to NULL so free_grid knows where to start
	map->grid = NULL;

	if (!read_metadata(fp, map))
		return (0);

	if (!init_grid(fp, map))
		return (0); // No grid allocated yet, or allocation failed

	if (!load_lines(fp, map))
	{
		// Smth went wrong while reading lines - CLEAN UP!
		free_grid(map);
		return (0);
	}

	return (1);
}
