/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_mlx.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erazumov <erazumov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/13 14:11:56 by erazumov          #+#    #+#             */
/*   Updated: 2026/01/06 17:13:18 by erazumov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/*
** Displays error message, cleans up allocated memory and exits.
*/
static void	mlx_fatal(t_game *game, char *msg)
{
	ft_putstr_fd("Error\n", 2);
	ft_putstr_fd(msg, 2);
	ft_putstr_fd("\n", 2);
	free_game(game);
	exit(1);
}

/*
** Creates a new window using MLX.
*/
static void	init_window(t_game *game)
{
	game->mlx_data->window = mlx_new_window(game->mlx_data->ptr_mlx,
			WIN_WIDTH, WIN_HEIGHT, "Cub3D");
	if (!game->mlx_data->window)
		mlx_fatal(game, "Window creation failed");
}

/*
** Creates main image buffer and gets its data address for pixel manipulation.
*/
static void	init_image(t_game *game)
{
	game->mlx_data->image = mlx_new_image(game->mlx_data->ptr_mlx,
			WIN_WIDTH, WIN_HEIGHT);
	if (!game->mlx_data->image)
		mlx_fatal(game, "Image creation failed");
	game->mlx_data->image_add = mlx_get_data_addr(game->mlx_data->image,
			&game->mlx_data->bits_per_pixel,
			&game->mlx_data->line_length,
			&game->mlx_data->endian);
	if (!game->mlx_data->image_add)
		mlx_fatal(game, "Image data addr failed");
}

/*
** Main initialisation routine for the graphical engine.
*/
void	init_mlx(t_game *game)
{
	game->mlx_data->ptr_mlx = mlx_init();
	if (!game->mlx_data->ptr_mlx)
		mlx_fatal(game, "MLX initialisation failed");
	init_window(game);
	init_image(game);
}
