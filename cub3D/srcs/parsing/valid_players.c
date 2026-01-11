/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   valid_players.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erazumov <erazumov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/27 12:11:56 by erazumov          #+#    #+#             */
/*   Updated: 2026/01/10 14:04:51 by erazumov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/*
** Checks if a character is a player marker (N/S/E/W).
** Replaces the marker with '0' and initialises vectors via set_angle.
*/
static int	save_player_pos(t_game *game, int x, int y)
{
	char	c;

	if (!game->map.grid[y])
		return (0);
	c = game->map.grid[y][x];
	if (ft_strchr("NSEW", c))
	{
		game->player.pos.x = (float)x + 0.5f;
		game->player.pos.y = (float)y + 0.5f;
		set_angle(&game->player, c);
		game->map.grid[y][x] = '0';
		return (1);
	}
	return (0);
}

/*
** Iterates through the map grid to find the player.
** Ensures exactly one player exists, otherwise returns 0.
*/
int	valid_players(t_game *game)
{
	int	x;
	int	y;
	int	players;

	y = 0;
	players = 0;
	while (game->map.grid[y] && y < game->map.height)
	{
		x = 0;
		while (game->map.grid[y][x])
		{
			if (save_player_pos(game, x, y))
				players++;
			x++;
		}
		y++;
	}
	if (players != 1)
	{
		ft_putstr_fd("Error\nMust have exactly one player (N/S/E/W)\n", 2);
		return (0);
	}
	return (1);
}

/*
** Executes core map validations: allowed characters and wall enclosure.
*/
int	run_map_checks(t_game *game)
{
	if (!valid_chars(game))
		return (0);
	if (!check_map_closed(game))
		return (0);
	return (1);
}

/*
** Entry point for map validation after grid conversion.
*/
int	valid_map(t_game *game)
{
	if (!valid_players(game))
		return (0);
	if (!run_map_checks(game))
		return (0);
	return (1);
}
