/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erazumov <erazumov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/10 20:29:47 by erazumov          #+#    #+#             */
/*   Updated: 2026/01/10 15:25:43 by erazumov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/*
** Validates command line arguments.
** Checks for exactly 2 arguments and the .cub extension.
*/
static int	check_args(int ac, char **av)
{
	int	len;

	if (ac != 2)
	{
		ft_putstr_fd("Error\nUsage: ./cub3D <map.cub>\n", 2);
		return (0);
	}
	len = ft_strlen(av[1]);
	if (len < 4 || ft_strncmp(av[1] + len - 4, ".cub", 4))
	{
		ft_putstr_fd("Error\nInvalid file extension (.cub required)\n", 2);
		return (0);
	}
	return (1);
}

/*
** Initialises MLX window, image buffer and loads game textures.
** Returns 1 on success, 0 if any MLX function or texture loading fails.
*/
static int	start_engine(t_game *game)
{
	game->mlx_data->window = mlx_new_window(game->mlx_data->ptr_mlx,
			WIN_WIDTH, WIN_HEIGHT, "cub3D");
	if (!game->mlx_data->window)
		return (0);
	game->mlx_data->image = mlx_new_image(game->mlx_data->ptr_mlx,
			WIN_WIDTH, WIN_HEIGHT);
	if (!game->mlx_data->image)
		return (0);
	game->mlx_data->image_add = mlx_get_data_addr(game->mlx_data->image,
			&game->mlx_data->bits_per_pixel, &game->mlx_data->line_length,
			&game->mlx_data->endian);
	if (!load_all_textures(game))
		return (0);
	init_hooks(game);
	return (1);
}

/*
** Initialises the player's direction and camera plane vectors.
** Uses the initial angle to calculate the direction vector (dir_x, dir_y)
** and sets the perpendicular camera plane (plane_x, plane_y) for FOV.
*/
void	init_player_vectors(t_game *game)
{
	game->player.dir_x = cos(game->player.angle);
	game->player.dir_y = sin(game->player.angle);
	game->player.plane_x = -0.66 * game->player.dir_y;
	game->player.plane_y = 0.66 * game->player.dir_x;
}

/*
** Main entry point of cub3D.
** Orchestrates parsing, player setup, and starts the MLX loop.
*/
int	main(int ac, char **av)
{
	t_game	game;

	if (!check_args(ac, av))
		return (1);
	init_game_struct(&game);
	game.mlx_data = init_mlx_data();
	if (!game.mlx_data)
	{
		ft_putstr_fd("Error\nMLX initialisation failed\n", 2);
		return (1);
	}
	if (!parse_file(av[1], &game))
	{
		free_game(&game);
		return (1);
	}
	init_player_vectors(&game);
	if (!start_engine(&game))
	{
		free_game(&game);
		return (1);
	}
	mlx_loop(game.mlx_data->ptr_mlx);
	return (0);
}
