/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mayoucha <mayoucha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/22 12:14:37 by mayoucha          #+#    #+#             */
/*   Updated: 2025/12/22 12:14:37 by mayoucha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/*
** Returns index of texture based on side hit and ray direction.
** NO = 0, SO = 1, WE = 2, EA = 3.
*/
int	get_tex_index(t_dda *d)
{
	if (d->side == 0)
	{
		if (d->ray_dir_x > 0)
			return (3);
		return (2);
	}
	else
	{
		if (d->ray_dir_y > 0)
			return (1);
		return (0);
	}
}

/*
** Loads a single texture from XPM file into memory using MiniLibX.
*/
int	load_texture(t_game *game, t_texture *tex, char *path)
{
	if (!path)
		return (0);
	tex->img_ptr = mlx_xpm_file_to_image(game->mlx_data->ptr_mlx, path,
			&tex->width, &tex->height);
	if (!tex->img_ptr)
		return (0);
	tex->addr = mlx_get_data_addr(tex->img_ptr, &tex->bpp,
			&tex->line_len, &tex->endian);
	if (!tex->addr)
		return (0);
	return (1);
}

/*
** Loads a single XPM texture into the game structure.
** Uses MiniLibX to convert the file to an image pointer and retrieves
** its data address for direct pixel access.
** If the path is invalid or loading fails, it triggers a clean exit.
*/
static int	load_single_texture(t_game *game, t_texture *tex, char *path)
{
	if (!path)
		close_game(game);
	tex->img_ptr = mlx_xpm_file_to_image(game->mlx_data->ptr_mlx, path,
			&tex->width, &tex->height);
	if (!tex->img_ptr)
	{
		ft_putstr_fd("Error\nInvalid texture path\n", 2);
		close_game(game);
	}
	tex->addr = mlx_get_data_addr(tex->img_ptr, &tex->bpp,
			&tex->line_len, &tex->endian);
	return (1);
}

/*
** Loads all four mandatory wall textures. Returns 0 on failure.
*/
int	load_all_textures(t_game *game)
{
	if (!load_single_texture(game, &game->tex[0], game->map.no_path))
		return (0);
	if (!load_single_texture(game, &game->tex[1], game->map.so_path))
		return (0);
	if (!load_single_texture(game, &game->tex[2], game->map.we_path))
		return (0);
	if (!load_single_texture(game, &game->tex[3], game->map.ea_path))
		return (0);
	return (1);
}
