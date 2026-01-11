/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_textures.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erazumov <erazumov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/07 16:29:24 by erazumov          #+#    #+#             */
/*   Updated: 2026/01/10 13:50:44 by erazumov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/*
** Charge une texture XPM et récupère son adresse mémoire (addr).
** C'est l'étape qui manquait pour voir les murs.
*/
static void	load_xpm(t_game *game, t_texture *tex, char *path)
{
	tex->img_ptr = mlx_xpm_file_to_image(game->mlx_data->ptr_mlx, path,
			&tex->width, &tex->height);
	if (!tex->img_ptr)
	{
		ft_putstr_fd("Error\nTexture path invalid: ", 2);
		ft_putstr_fd(path, 2);
		close_game(game);
	}
	tex->addr = mlx_get_data_addr(tex->img_ptr, &tex->bpp,
			&tex->line_len, &tex->endian);
	if (!tex->addr)
		close_game(game);
}

/*
** Initialise les 4 textures cardinales.
*/
void	init_textures(t_game *game)
{
	load_xpm(game, &game->tex[0], game->map.no_path);
	load_xpm(game, &game->tex[1], game->map.so_path);
	load_xpm(game, &game->tex[2], game->map.we_path);
	load_xpm(game, &game->tex[3], game->map.ea_path);
}
