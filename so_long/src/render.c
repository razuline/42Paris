/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erazumov <erazumov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 20:20:11 by erazumov          #+#    #+#             */
/*   Updated: 2025/04/21 13:45:51 by erazumov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static void	draw_map(t_game *game);
static void	draw_tile(t_game *game, int x, int y);
static void	draw_player(t_game *game);
static void	img_to_window(t_game *game, void *img, int x, int y);

int	render_frame(t_game *game)
{
	draw_map(game);
	draw_player(game);
	return (0);
}

static void	draw_map(t_game *game)
{
	int	x;
	int	y;

	y = 0;
	while (y < game->map.height)
	{
		x = 0;
		while (x < game->map.width)
		{
			draw_tile(game, x, y);
			x++;
		}
		y++;
	}
}

static void	draw_tile(t_game *game, int x, int y)
{
	char	tile_type;

	tile_type = game->map.grid[y][x];
	if (tile_type != WALL)
		img_to_window(game, game->tex.floor, x, y);
	if (tile_type == WALL)
		img_to_window(game, game->tex.wall, x, y);
	else if (tile_type == COLLECTIBLE)
		img_to_window(game, game->tex.collect, x, y);
	else if (tile_type == EXIT)
	{
		if (game->exit_access)
			img_to_window(game, game->tex.exit_open, x, y);
		else
			img_to_window(game, game->tex.exit_closed, x, y);
	}
}

static void	draw_player(t_game *game)
{
	img_to_window(game, game->tex.player,
		game->player_pos.x, game->player_pos.y);
}

static void	img_to_window(t_game *game, void *img, int x, int y)
{
	int	pixel_x;
	int	pixel_y;

	if (!img)
		return ;
	pixel_x = x * TILE_SIZE;
	pixel_y = y * TILE_SIZE;
	mlx_put_image_to_window(game->mlx, game->win, img, pixel_x, pixel_y);
}
