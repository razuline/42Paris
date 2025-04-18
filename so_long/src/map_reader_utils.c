/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_reader_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erazumov <erazumov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 17:12:41 by erazumov          #+#    #+#             */
/*   Updated: 2025/04/18 11:27:48 by erazumov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	trim_newline(char *line)
{
	int	len;

	if (!line)
		return ;
	len = ft_strlen(line);
	if (len > 0 && line[len - 1] == '\n')
		line[len - 1] = '\0';
}

int	process_dimen_line(char *line, t_game *game, int *first_line)
{
	int	curr_width;

	if (*line != '\0')
	{
		trim_newline(line);
		curr_width = ft_strlen(line);
		if (*first_line)
		{
			game->map.width = curr_width;
			if (game->map.width == 0)
			{
				free(line);
				return (-1);
			}
			*first_line = 0;
		}
		game->map.height++;
	}
	free(line);
	return (0);
}

void	cleanup_fill_error(t_game *game, int count)
{
	int	i;

	if (!game->map.grid)
		return ;
	i = 0;
	while (i < count)
	{
		if (game->map.grid[i])
			free(game->map.grid[i]);
		i++;
	}
	free(game->map.grid);
	game->map.grid = NULL;
}

int	check_remain_lines(int fd)
{
	char	*line;
	int		existed;

	existed = 0;
	line = get_next_line(fd);
	if (line != NULL)
	{
		if (*line != '\0')
			existed = 1;
		free(line);
	}
	if (existed)
		return (-1);
	return (0);
}

int	allocate_grid(t_game *game)
{
	if (game->map.height <= 0)
		return (-1);
	game->map.grid = (char **)malloc(sizeof(char *) * (game->map.height + 1));
	if (!game->map.grid)
		return (-1);
	game->map.grid[game->map.height] = NULL;
	return (0);
}
