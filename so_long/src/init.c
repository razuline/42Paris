/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erazumov <erazumov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 20:07:57 by erazumov          #+#    #+#             */
/*   Updated: 2025/04/21 15:58:07 by erazumov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

#define WALL_XPM        "images/wall.xpm"
#define FLOOR_XPM       "images/floor.xpm"
#define COLLECTIBLE_XPM "images/collectible.xpm"
#define PLAYER_XPM      "images/player.xpm"
#define EXIT_CLOSED_XPM "images/exit_closed.xpm"
#define EXIT_OPEN_XPM   "images/exit_open.xpm"

static void	init_mlx_and_window(t_game *game);
static void	load_all_textures(t_game *game);
static void	load_one_texture(t_game *game, void **texture_ptr, char *path);

void	init_game(t_game *game)
{
	init_mlx_and_window(game);
	load_all_textures(game);
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

static void	load_all_textures(t_game *game)
{
	load_one_texture(game, &game->tex.wall, WALL_XPM);
	load_one_texture(game, &game->tex.floor, FLOOR_XPM);
	load_one_texture(game, &game->tex.collect, COLLECTIBLE_XPM);
	load_one_texture(game, &game->tex.player, PLAYER_XPM);
	load_one_texture(game, &game->tex.exit_closed, EXIT_CLOSED_XPM);
	load_one_texture(game, &game->tex.exit_open, EXIT_OPEN_XPM);
}

static void	handle_texture_error(t_game *game, char *path, char *reason,
	t_point size)
{
	ft_putstr_fd("Error\nTexture Error: ", 2);
	ft_putstr_fd(reason, 2);
	ft_putstr_fd("\nPath: ", 2);
	ft_putstr_fd(path, 2);
	if (size.x > 0)
	{
		ft_putstr_fd("\nSize: ", 2);
		ft_putnbr_fd(size.x, 2);
		ft_putstr_fd("x", 2);
		ft_putnbr_fd(size.y, 2);
		ft_putstr_fd(" Expected: ", 2);
		ft_putnbr_fd(TILE_SIZE, 2);
		ft_putstr_fd("x", 2);
		ft_putnbr_fd(TILE_SIZE, 2);
	}
	ft_putstr_fd("\n", 2);
	cleanup_game(game);
	exit(EXIT_FAILURE);
}

static void	load_one_texture(t_game *game, void **texture_ptr, char *path)
{
	int		width;
	int		height;
	t_point	img_size;

	*texture_ptr = mlx_xpm_file_to_image(game->mlx, path, &width, &height);
	if (*texture_ptr == NULL)
		handle_texture_error(game, path, "Failed to load", (t_point){-1, -1});
	if (width != TILE_SIZE || height != TILE_SIZE)
	{
		img_size.x = width;
		img_size.y = height;
		handle_texture_error(game, path, "Wrong size", img_size);
	}
}
