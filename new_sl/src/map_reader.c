/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_reader.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erazumov <erazumov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 14:13:49 by erazumov          #+#    #+#             */
/*   Updated: 2025/04/17 15:29:33 by erazumov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

static void	trim_newline(char *line)
{
	int	len;

	if (!line)
		return;
	len = ft_strlen(line);
	if (len > 0 && line[len - 1] == '\n')
	{
		line[len - 1] = '\0';
	}
}

static int	get_map_dimensions(int fd, t_game *game)
{
	char	*line;
	int		first_line;

	game->map.height = 0;
	game->map.width = -1;
	first_line = 1;
	while ((line = get_next_line(fd)) != NULL)
	{
		if (*line != '\0')
		{
			trim_newline(line);
			if (first_line)
			{
				game->map.width = ft_strlen(line);
				if (game->map.width == 0)
				{
					free(line);
					return (-1);
				}
				first_line = 0;
			}
			game->map.height++;
		}
		free(line);
	}
	if (game->map.height == 0 || game->map.width <= 0)
		return (-1);
	return (0);
}

static int	allocate_grid(t_game *game)
{
	if (game->map.height <= 0)
		return (-1);
	game->map.grid = (char **)malloc(sizeof(char *) * (game->map.height + 1));
	if (!game->map.grid)
		return (-1);
	game->map.grid[game->map.height] = NULL;
	return (0);
}

static int	fill_grid(int fd, t_game *game)
{
	char	*line;
	int		i;

	i = 0;
	while (i < game->map.height)
	{
		line = get_next_line(fd);
		if (line == NULL)
		{
			while (--i >= 0)
				free(game->map.grid[i]);
			free(game->map.grid);
			game->map.grid = NULL;
			return (-1);
		}
		if (*line != '\0')
		{
			trim_newline(line);
			game->map.grid[i] = line;
			i++;
		}
		else
			free(line);
	}
	line = get_next_line(fd);
	if (line != NULL)
	{
		if (*line != '\0')
		{
			free(line);
			while (--i >= 0)
				free(game->map.grid[i]);
			free(game->map.grid);
			game->map.grid = NULL;
			return (-1);
		}
		free(line);
	}
	return (0);
}

void	read_map(char *filename, t_game *game)
{
	int		fd;

	fd = open(filename, O_RDONLY);
	if (fd < 0)
		exit_error(game, "Could not open map file.");
	if (get_map_dimensions(fd, game) < 0)
	{
		close(fd);
		exit_error(game, "Failed to read map dimensions or map is empty/invalid.");
	}
	close(fd);
	if (allocate_grid(game) < 0)
		exit_error(game, "Memory allocation failed for map grid.");
	fd = open(filename, O_RDONLY);
	if (fd < 0)
		exit_error(game, "Could not reopen map file for second read.");
	if (fill_grid(fd, game) < 0)
	{
		close(fd);
		exit_error(game, "Failed to fill map grid or map format error.");
	}
	close(fd);
}
