/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erazumov <erazumov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 10:51:23 by erazumov          #+#    #+#             */
/*   Updated: 2025/03/12 11:24:48 by erazumov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "so_long.h"

void	free_game(t_game *game)
{
	if (game->img.player_img)
		mlx_destroy_image(game->mlx, game->img.player_img);
	if (game->img.wall_img)
		mlx_destroy_image(game->mlx, game->img.wall_img);
	if (game->img.floor_img)
		mlx_destroy_image(game->mlx, game->img.floor_img);
	if (game->img.object_img)
		mlx_destroy_image(game->mlx, game->img.object_img);
	if (game->img.exit_img)
		mlx_destroy_image(game->mlx, game->img.exit_img);
	if (game->map.grid)
		free_map(&game->map);	
	if (game->win)
		mlx_destroy_window(game->mlx, game->win);
	if (game->mlx)
		free(game->mlx);
}

void	free_map(t_map *map)
{
	int	i;

	i = 0;
	while (map->grid[i])
	{
		free(map->grid[i]);
		i++;
	}
	free(map->grid);
	map->grid = NULL;
}
