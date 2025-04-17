/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erazumov <erazumov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 20:56:22 by erazumov          #+#    #+#             */
/*   Updated: 2025/04/17 21:17:48 by erazumov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	free_map_grid(char **grid, int height)
{
	int	y;

	if (!grid)
		return ;
	y = 0;
	while (y < height)
	{
		if (grid[y])
			free(grid[y]);
		y++;
	}
	free(grid);
}

void	destroy_textures(t_game *game)
{
	if (!game->mlx)
		return ;
	if (game->tex.wall)
		mlx_destroy_image(game->mlx, game->tex.wall);
	if (game->tex.floor)
		mlx_destroy_image(game->mlx, game->tex.floor);
	if (game->tex.collect)
		mlx_destroy_image(game->mlx, game->tex.collect);
	if (game->tex.player)
		mlx_destroy_image(game->mlx, game->tex.player);
	if (game->tex.exit_closed)
		mlx_destroy_image(game->mlx, game->tex.exit_closed);
	if (game->tex.exit_open)
		mlx_destroy_image(game->mlx, game->tex.exit_open);
	ft_memset(&game->tex, 0, sizeof(t_textures));
}

static void	cleanup_mlx(t_game *game)
{
	if (game->win)
	{
		mlx_destroy_window(game->mlx, game->win);
		game->win = NULL;
	}
	if (game->mlx)
	{
		mlx_destroy_display(game->mlx);
		free(game->mlx);
		game->mlx = NULL;
	}
}

void	cleanup_game(t_game *game)
{
	free_map_grid(game->map.grid, game->map.height);
	game->map.grid = NULL;
	destroy_textures(game);
	cleanup_mlx(game);
}

void	exit_game(t_game *game, int exit_code)
{
	ft_printf("Exiting game...\n");
	cleanup_game(game);
	exit(exit_code);
}
