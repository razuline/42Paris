/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_valid_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erazumov <erazumov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 18:06:03 by erazumov          #+#    #+#             */
/*   Updated: 2025/04/17 18:33:21 by erazumov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

int	check_horiz_walls(t_game *game)
{
	int	x;
	int	width;
	int	height;

	width = game->map.width;
	height = game->map.height;
	x = 0;
	while (x < width)
	{
		if (game->map.grid[0][x] != WALL)
			return (0);
		x++;
	}
	x = 0;
	while (x < width)
	{
		if (game->map.grid[height - 1][x] != WALL)
			return (0);
		x++;
	}
	return (1);
}

int	check_vert_walls(t_game *game)
{
	int	y;
	int	width;
	int	height;

	width = game->map.width;
	height = game->map.height;
	y = 1;
	while (y < height - 1)
	{
		if (game->map.grid[y][0] != WALL)
			return (0);
		if (game->map.grid[y][width - 1] != WALL)
			return (0);
		y++;
	}
	return (1);
}

int	is_valid_char(char c)
{
	if (c == WALL || c == FLOOR || c == COLLECTIBLE || c == EXIT
			|| c == PLAYER)
		return (1);
	return (0);
}

void	update_counts(char c, t_game *game, int x, int y, int counts[3])
{
	if (c == PLAYER)
	{
		counts[0]++;
		game->player_pos.x = x;
		game->player_pos.y = y;
	}
	else if (c == EXIT)
		counts[1]++;
	else if (c == COLLECTIBLE)
		counts[2]++;
}

int	final_count_check(t_game *game, int counts[3])
{
	if (counts[0] != 1)
	{
		print_error("Map must contain exactly one player 'P'.");
		return (0);
	}
	if (counts[1] != 1)
	{
		print_error("Map must contain exactly one exit 'E'.");
		return (0);
	}
	if (counts[2] < 1)
	{
		print_error("Map must contain at least one collectible 'C'.");
		return (0);
	}
	game->collect_total = counts[2];
	game->collect_curr = counts[2];
	return (1);
}
