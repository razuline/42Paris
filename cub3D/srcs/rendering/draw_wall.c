/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_wall.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mayoucha <mayoucha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/22 12:14:18 by mayoucha          #+#    #+#             */
/*   Updated: 2025/12/22 12:14:18 by mayoucha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/*
** Performs DDA algorithm to find the point where the ray hits a wall.
** Updates map coordinates and checks grid for '1' (wall).
*/
static int	dda_loop(t_dda *d, t_game *game)
{
	int	hit;

	hit = 0;
	while (!hit)
	{
		if (d->side_dist_x < d->side_dist_y)
		{
			d->side_dist_x += d->delta_dist_x;
			d->map_x += d->step_x;
			d->side = 0;
		}
		else
		{
			d->side_dist_y += d->delta_dist_y;
			d->map_y += d->step_y;
			d->side = 1;
		}
		if (d->map_y < 0 || d->map_y >= game->map.height
			|| d->map_x < 0 || d->map_x >= game->map.width)
			return (0);
		if (game->map.grid[d->map_y][d->map_x] == '1')
			hit = 1;
	}
	return (1);
}

/*
** Fills the ceiling and floor with their respective colors.
*/
void	draw_c_f(t_game *game, int col, int start_y, int end_y)
{
	int	y;

	y = 0;
	while (y < start_y)
	{
		put_pixel(col, y, game->map.ceiling_color, game);
		y++;
	}
	y = end_y;
	while (y < WIN_HEIGHT)
	{
		put_pixel(col, y, game->map.floor_color, game);
		y++;
	}
}

/*
** Main raycasting entry point for a single screen column.
*/
void	draw_line(t_player *player, t_game *game, int col)
{
	t_dda	d;
	float	camera_x;

	camera_x = 2.0f * col / (float)WIN_WIDTH - 1.0f;
	init_dda(&d, player, camera_x);
	if (dda_loop(&d, game))
		draw_wall_slice(col, &d, game);
}
