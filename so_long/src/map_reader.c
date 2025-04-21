/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_reader.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erazumov <erazumov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 14:13:49 by erazumov          #+#    #+#             */
/*   Updated: 2025/04/21 14:06:20 by erazumov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static int	do_first_pass(char *filename, t_game *game);
static int	get_map_dimen(int fd, t_game *game);
static int	do_second_pass(char *filename, t_game *game);
static int	fill_grid_loop(int fd, t_game *game);

void	read_map(char *filename, t_game *game)
{
	int		status;

	status = do_first_pass(filename, game);
	if (status < 0)
		exit_error(game, "Failed to read map dimensions or map is"
				"empty/invalid.");
	status = allocate_grid(game);
	if (status < 0)
		exit_error(game, "Memory allocation failed for map grid.");
	status = do_second_pass(filename, game);
	if (status < 0)
		exit_error(game, "Failed to fill map grid or extra lines"
				"found in file.");
}

static int	do_first_pass(char *filename, t_game *game)
{
	int		fd;
	int		status;

	fd = open(filename, O_RDONLY);
	if (fd < 0)
		return (-1);
	status = 0;
	status = get_map_dimen(fd, game);
	close(fd);
	if (status < 0)
		return (-1);
	return (0);
}

static int	get_map_dimen(int fd, t_game *game)
{
	char	*line;
	int		first_line;
	int		status;

	game->map.height = 0;
	game->map.width = -1;
	first_line = 1;
	status = 0;
	while (status == 0)
	{
		line = get_next_line(fd);
		if (line == NULL)
			break ;
		status = process_dimen_line(line, game, &first_line);
	}
	if (status == 0 && (game->map.height == 0 || game->map.width <= 0))
		return (-1);
	if (status < 0)
		return (-1);
	return (0);
}

static int	do_second_pass(char *filename, t_game *game)
{
	int		fd;
	int		status;

	fd = open(filename, O_RDONLY);
	if (fd < 0)
		return (-1);
	status = fill_grid_loop(fd, game);
	if (status == 0)
		status = check_remain_lines(fd);
	close(fd);
	if (status < 0)
	{
		cleanup_fill_error(game, game->map.height);
		return (-1);
	}
	return (0);
}

static int	fill_grid_loop(int fd, t_game *game)
{
	char	*line;
	int		i;

	i = 0;
	while (i < game->map.height)
	{
		line = get_next_line(fd);
		if (line == NULL)
		{
			cleanup_fill_error(game, i);
			return (-1);
		}
		if (*line == '\0')
		{
			free(line);
			continue ;
		}
		trim_newline(line);
		game->map.grid[i] = line;
		i++;
	}
	return (0);
}


