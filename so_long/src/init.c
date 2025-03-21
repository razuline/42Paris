/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erazumov <erazumov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 15:51:16 by erazumov          #+#    #+#             */
/*   Updated: 2025/03/21 14:09:13 by erazumov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "so_long.h"

void	load_images(t_game *game)
{
	game->img.player_img = mlx_xpm_file_to_image(game->mlx, "assets/player.xpm",
		&game->map.width, &game->map.height);
	game->img.wall_img = mlx_xpm_file_to_image(game->mlx, "assets/wall.xpm",
		&game->map.width, &game->map.height);
	game->img.floor_img = mlx_xpm_file_to_image(game->mlx, "assets/floor.xpm",
		&game->map.width, &game->map.height);
	game->img.object_img = mlx_xpm_file_to_image(game->mlx, "assets/object.xpm",
		&game->map.width, &game->map.height);
	game->img.exit_img = mlx_xpm_file_to_image(game->mlx, "assets/exit.xpm",
		&game->map.width, &game->map.height);
	if (!game->img.player_img || !game->img.wall_img || !game->img.floor_img || 
		!game->img.object_img || !game->img.exit_img)
	{
		ft_printf("Error: failed to load textures.\n");
		free_game(game);
		exit(1);
	}
}

int	init_game(t_game *game, char *map_file)
{
	game->mlx = mlx_init();
	if (!game->mlx || !parse_map(&game->map, map_file))
		return (0);
	game->win = mlx_new_window(game->mlx, game->map.width * TILE_SIZE,
		game->map.height * TILE_SIZE, "so_long");
	if (!game->win)
		return (0);
	load_images(game);
	render_game(game);
	return (1);
}
