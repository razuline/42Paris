/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mayoucha <mayoucha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/20 12:25:54 by mayoucha          #+#    #+#             */
/*   Updated: 2025/12/20 12:25:54 by mayoucha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/*
** Basic collision check: returns 1 if coordinates hit a wall ('1').
*/
int	touch(float px, float py, t_game *game)
{
	int		x;
	int		y;

	x = (int)px;
	y = (int)py;
	if (y < 0 || x < 0 || y >= game->map.height || x >= game->map.width)
		return (1);
	if (game->map.grid[y][x] == '1')
		return (1);
	return (0);
}

/*
** Wipes the image buffer before drawing the next frame.
*/
void	clear_image(t_game *game)
{
	int	y;
	int	x;
	int	c_color;
	int	f_color;

	c_color = (game->ceiling.r << 16 | game->ceiling.g << 8 | game->ceiling.b);
	f_color = (game->floor.r << 16 | game->floor.g << 8 | game->floor.b);
	y = 0;
	while (y < WIN_HEIGHT)
	{
		x = 0;
		while (x < WIN_WIDTH)
		{
			if (y < WIN_HEIGHT / 2)
				put_pixel(x, y, c_color, game);
			else
				put_pixel(x, y, f_color, game);
			x++;
		}
		y++;
	}
}
