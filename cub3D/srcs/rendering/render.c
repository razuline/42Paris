/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erazumov <erazumov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/30 10:22:34 by mayoucha          #+#    #+#             */
/*   Updated: 2026/01/10 14:39:30 by erazumov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/*
** Calculates perpendicular distance to the wall to avoid fisheye effect.
** Returns the distance, with a minimum threshold to avoid division by zero.
*/
static float	get_perp_dist(t_dda *d)
{
	if (d->side == 0)
		return (d->side_dist_x - d->delta_dist_x);
	else
		return (d->side_dist_y - d->delta_dist_y);
}

/*
** Calculates the height of the wall on screen and its start/end Y coordinates.
** Clamps values to window height boundaries.
*/
static void	compute_wall_bounds(float perp_dist, float *height, int *start,
			int *end)
{
	*height = (int)(WIN_HEIGHT / perp_dist);
	*start = -(*height) / 2 + WIN_HEIGHT / 2;
	if (*start < 0)
		*start = 0;
	*end = (*height) / 2 + WIN_HEIGHT / 2;
	if (*end >= WIN_HEIGHT)
		*end = WIN_HEIGHT - 1;
}

/*
** Determines exact X coordinate on the texture based on where the ray hit.
*/
static int	compute_tex_x(t_dda *d, t_game *game, t_texture *tex,
			float perp_dist)
{
	float	wall_x;
	int		tex_x;

	if (d->side == 0)
		wall_x = game->player.pos.y + perp_dist * d->ray_dir_y;
	else
		wall_x = game->player.pos.x + perp_dist * d->ray_dir_x;
	wall_x -= floor(wall_x);
	tex_x = (int)(wall_x * tex->width);
	if ((d->side == 0 && d->ray_dir_x > 0)
		|| (d->side == 1 && d->ray_dir_y < 0))
		tex_x = tex->width - tex_x - 1;
	return (tex_x);
}

/*
** Renders a single vertical column of wall pixels using texture mapping.
*/
static void	render_wall_column(t_game *game, t_texture *tex, int col, t_wall *w)
{
	float	step;
	float	tex_pos;
	int		y;
	int		tex_y;
	int		color;

	step = (float)tex->height / w->height;
	tex_pos = (w->start - WIN_HEIGHT / 2 + w->height / 2) * step;
	if (tex_pos < 0)
		tex_pos = 0;
	y = w->start;
	while (y < w->end)
	{
		tex_y = (int)tex_pos;
		if (tex_y >= tex->height)
			tex_y = tex->height - 1;
		color = *(int *)(tex->addr + (tex_y * tex->line_len)
				+ (w->tex_x * (tex->bpp / 8)));
		put_pixel(col, y, color, game);
		tex_pos += step;
		y++;
	}
}

/*
** Orchestrates the drawing of a single wall slice (ceiling, wall, floor).
*/
void	draw_wall_slice(int col, t_dda *d, t_game *game)
{
	t_texture	*tex;
	t_wall		w;
	float		perp_dist;

	perp_dist = get_perp_dist(d);
	if (perp_dist <= 0)
		perp_dist = 0.1f;
	tex = &game->tex[get_tex_index(d)];
	compute_wall_bounds(perp_dist, &w.height, &w.start, &w.end);
	draw_c_f(game, col, w.start, w.end);
	w.tex_x = compute_tex_x(d, game, tex, perp_dist);
	render_wall_column(game, tex, col, &w);
}
