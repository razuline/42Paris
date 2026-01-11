/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erazumov <erazumov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/04 20:27:26 by mayoucha          #+#    #+#             */
/*   Updated: 2026/01/06 15:40:21 by erazumov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/*
** Calculates the ray direction and initial map cell position.
*/
static void	init_ray_dir_and_map(t_dda *d, t_player *p, float camera_x)
{
	d->ray_dir_x = p->dir_x + p->plane_x * camera_x;
	d->ray_dir_y = p->dir_y + p->plane_y * camera_x;
	d->map_x = (int)p->pos.x;
	d->map_y = (int)p->pos.y;
}

/*
** Calculates the distance the ray has to travel to go from one grid line 
** to the next (delta_dist).
*/
static void	init_delta_dist(t_dda *d)
{
	if (d->ray_dir_x == 0.0f)
		d->delta_dist_x = 1e30;
	else
		d->delta_dist_x = fabs(1.0f / d->ray_dir_x);
	if (d->ray_dir_y == 0.0f)
		d->delta_dist_y = 1e30;
	else
		d->delta_dist_y = fabs(1.0f / d->ray_dir_y);
}

/*
** Calculates the step direction and the initial distance from the player
** position to the first grid line (side_dist).
*/
static void	init_step_and_side_dist(t_dda *d, t_player *p)
{
	if (d->ray_dir_x < 0.0f)
	{
		d->step_x = -1;
		d->side_dist_x = (p->pos.x - d->map_x) * d->delta_dist_x;
	}
	else
	{
		d->step_x = 1;
		d->side_dist_x = (d->map_x + 1.0f - p->pos.x) * d->delta_dist_x;
	}
	if (d->ray_dir_y < 0.0f)
	{
		d->step_y = -1;
		d->side_dist_y = (p->pos.y - d->map_y) * d->delta_dist_y;
	}
	else
	{
		d->step_y = 1;
		d->side_dist_y = (d->map_y + 1.0f - p->pos.y) * d->delta_dist_y;
	}
}

/*
** Entry point for DDA initialisation before the main hit loop.
*/
void	init_dda(t_dda *d, t_player *p, float camera_x)
{
	init_ray_dir_and_map(d, p, camera_x);
	init_delta_dist(d);
	init_step_and_side_dist(d, p);
}
