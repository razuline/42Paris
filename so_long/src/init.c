/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erazumov <erazumov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 20:07:57 by erazumov          #+#    #+#             */
/*   Updated: 2025/04/17 20:23:33 by erazumov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

#define WALL_XPM        "textures/wall.xpm"
#define FLOOR_XPM       "textures/floor.xpm"
#define COLLECTIBLE_XPM "textures/collectible.xpm"
#define PLAYER_XPM      "textures/player.xpm"
#define EXIT_CLOSED_XPM "textures/exit_closed.xpm"
#define EXIT_OPEN_XPM   "textures/exit_open.xpm"

static void	load_one_texture(t_game *game, void **texture_ptr, char *path)
{
	int	width;
	int	height;

	*texture_ptr = mlx_xpm_file_to_image(game->mlx, path, &width, &height);
	if (*texture_ptr == NULL)
	{
		char msg_buffer[100];
		sprintf(msg_buffer, "Failed to load texture: %s", path);
		exit_error(game, msg_buffer);
	}
	if (width != TILE_SIZE || height != TILE_SIZE)
	{
		printf("Warning: Texture '%s' size (%dx%d) differs from TILE_SIZE (%d)\n",
				path, width, height, TILE_SIZE);
		char msg_buffer[150];
		sprintf(msg_buffer, "Texture %s has wrong size (%dx%d), expected %dx%d",
				path, width, height, TILE_SIZE, TILE_SIZE);
		exit_error(game, msg_buffer);
	}
}

static void	load_all_textures(t_game *game)
{
	load_one_texture(game, &game->tex.wall, WALL_XPM);
	load_one_texture(game, &game->tex.floor, FLOOR_XPM);
	load_one_texture(game, &game->tex.collect, COLLECTIBLE_XPM);
	load_one_texture(game, &game->tex.player, PLAYER_XPM);
	load_one_texture(game, &game->tex.exit_closed, EXIT_CLOSED_XPM);
	load_one_texture(game, &game->tex.exit_open, EXIT_OPEN_XPM);
}

static void	init_mlx_and_window(t_game *game)
{
	int	win_width;
	int	win_height;

	game->mlx = mlx_init();
	if (game->mlx == NULL)
		exit_error(game, "Failed to initialize MiniLibX.");
	win_width = game->map.width * TILE_SIZE;
	win_height = game->map.height * TILE_SIZE;
	game->win = mlx_new_window(game->mlx, win_width, win_height, "so_long");
	if (game->win == NULL)
		exit_error(game, "Failed to create game window.");
}

void	init_game(t_game *game)
{
	init_mlx_and_window(game);
	load_all_textures(game);
}
