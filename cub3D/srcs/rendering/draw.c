/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erazumov <erazumov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/04 20:27:34 by mayoucha          #+#    #+#             */
/*   Updated: 2026/01/10 14:29:52 by erazumov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/*
** Main drawing loop called by mlx_loop_hook.
** Updates player physics and renders the scene column by column.
*/
int	draw_loop(t_game *game)
{
	t_player	*player;
	int			i;

	player = &game->player;
	move_player(player, game);
	i = 0;
	while (i < WIN_WIDTH)
	{
		draw_line(player, game, i);
		i++;
	}
	mlx_put_image_to_window(game->mlx_data->ptr_mlx, game->mlx_data->window,
		game->mlx_data->image, 0, 0);
	return (0);
}

/*
** Writes a color to a specific pixel in the image buffer.
** Handles window boundaries to prevent memory corruption.
*/
void	put_pixel(int x, int y, int color, t_game *game)
{
	int	offset;

	if (x >= WIN_WIDTH || y >= WIN_HEIGHT || x < 0 || y < 0)
		return ;
	offset = y * game->mlx_data->line_length + x
		* (game->mlx_data->bits_per_pixel / 8);
	game->mlx_data->image_add[offset] = color & 0xFF;
	game->mlx_data->image_add[offset + 1] = (color >> 8) & 0xFF;
	game->mlx_data->image_add[offset + 2] = (color >> 16) & 0xFF;
	game->mlx_data->image_add[offset + 3] = (color >> 24);
}
