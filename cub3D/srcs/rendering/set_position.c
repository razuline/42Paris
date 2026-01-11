/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_position.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erazumov <erazumov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/23 16:09:04 by mayoucha          #+#    #+#             */
/*   Updated: 2026/01/10 14:40:04 by erazumov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/*
** Initialises player coordinates at the center of the grid cell.
*/
static void	set_coordinates(t_game *game, int x, int y, char c)
{
	game->player.pos.x = (float)x + 0.5f;
	game->player.pos.y = (float)y + 0.5f;
	set_angle(&game->player, c);
}

/*
** Scans the map to find the player marker and initialises position.
*/
void	set_player_position(t_game *game)
{
	int		y;
	int		x;
	char	c;

	y = 0;
	while (game->map.grid[y] && y < game->map.height)
	{
		x = 0;
		while (game->map.grid[y][x])
		{
			c = game->map.grid[y][x];
			if (c == 'N' || c == 'S' || c == 'E' || c == 'W')
			{
				set_coordinates(game, x, y, c);
				return ;
			}
			x++;
		}
		y++;
	}
}
