/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erazumov <erazumov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/21 15:03:41 by erazumov          #+#    #+#             */
/*   Updated: 2026/01/10 15:36:54 by erazumov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/*
** Frees the 2D map grid and the line length array.
*/
static void	free_map(t_game *game)
{
	int	i;

	if (!game->map.grid)
		return ;
	i = 0;
	while (game->map.grid[i])
	{
		free(game->map.grid[i]);
		i++;
	}
	free(game->map.grid);
	game->map.grid = NULL;
	if (game->map.line_len)
	{
		free(game->map.line_len);
		game->map.line_len = NULL;
	}
}

/*
** Frees both the allocated paths and MLX images for all textures.
*/
void	free_textures(t_game *game)
{
	int	i;

	if (game->map.no_path)
		free(game->map.no_path);
	if (game->map.so_path)
		free(game->map.so_path);
	if (game->map.we_path)
		free(game->map.we_path);
	if (game->map.ea_path)
		free(game->map.ea_path);
	if (!game->mlx_data)
		return ;
	i = 0;
	while (i < 4)
	{
		if (game->tex[i].img_ptr)
		{
			mlx_destroy_image(game->mlx_data->ptr_mlx, game->tex[i].img_ptr);
			game->tex[i].img_ptr = NULL;
		}
		i++;
	}
}

/*
** Final cleanup: destroys window, image buffer, and frees structures.
*/
void	free_game(t_game *game)
{
	if (!game)
		return ;
	free_map(game);
	free_textures(game);
	if (game->mlx_data)
	{
		if (game->mlx_data->image)
			mlx_destroy_image(game->mlx_data->ptr_mlx, game->mlx_data->image);
		if (game->mlx_data->window)
			mlx_destroy_window(game->mlx_data->ptr_mlx, game->mlx_data->window);
		if (game->mlx_data->ptr_mlx)
		{
			mlx_destroy_display(game->mlx_data->ptr_mlx);
			free(game->mlx_data->ptr_mlx);
		}
		free(game->mlx_data);
		game->mlx_data = NULL;
	}
}
