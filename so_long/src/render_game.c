/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_game.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erazumov <erazumov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 11:28:56 by erazumov          #+#    #+#             */
/*   Updated: 2025/03/21 14:09:43 by erazumov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "so_long.h"

void	render_square(t_game *game, char square, int x, int y)
{
	if (square == '1') /* Wall */
		mlx_put_image_to_window(game->mlx, game->win, game->img.wall_img,
			x * TILE_SIZE, y * TILE_SIZE);
	else if (square == '0') /* Floor */
		mlx_put_image_to_window(game->mlx, game->win, game->img.floor_img,
			x * TILE_SIZE, y * TILE_SIZE);
	else if (square == 'P') /* Player */
		mlx_put_image_to_window(game->mlx, game->win, game->img.player_img,
			x * TILE_SIZE, y * TILE_SIZE);
	else if (square == 'C') /* Object */
		mlx_put_image_to_window(game->mlx, game->win, game->img.object_img,
			x * TILE_SIZE, y * TILE_SIZE);
	else if (square == 'E') /* Exit */
		mlx_put_image_to_window(game->mlx, game->win, game->img.exit_img,
			x * TILE_SIZE, y * TILE_SIZE);
}

void	render_game(t_game *game)
{
	int	i;
	int	j;

	i = 0;
	while (i < game->map.height) /* Lines of map */
	{
		j = 0;
		while (j < game->map.width) /* Rows of map */
		{
			render_square(game, game->map.grid[i][j], j, i);
			j++;
		}
		i++;
	}
}
