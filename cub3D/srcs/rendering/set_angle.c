/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_angle.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erazumov <erazumov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/23 16:16:53 by mayoucha          #+#    #+#             */
/*   Updated: 2026/01/12 19:29:01 by erazumov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/*
** Vector setup for North and South orientations.
*/
static void	set_ns_angle(t_player *p, char c)
{
	if (c == 'N')
	{
		p->angle = -PI / 2;
		p->dir_x = 0.0f;
		p->dir_y = -1.0f;
		p->plane_x = 0.66f;
		p->plane_y = 0.0f;
	}
	else if (c == 'S')
	{
		p->angle = PI / 2;
		p->dir_x = 0.0f;
		p->dir_y = 1.0f;
		p->plane_x = -0.66f;
		p->plane_y = 0.0f;
	}
}

/*
** Vector setup for East and West orientations.
*/
static void	set_ew_angle(t_player *p, char c)
{
	if (c == 'E')
	{
		p->angle = 0.0f;
		p->dir_x = 1.0f;
		p->dir_y = 0.0f;
		p->plane_x = 0.0f;
		p->plane_y = 0.66f;
	}
	else if (c == 'W')
	{
		p->angle = PI;
		p->dir_x = -1.0f;
		p->dir_y = 0.0f;
		p->plane_x = 0.0f;
		p->plane_y = -0.66f;
	}
}

/*
** Main router to initialise vectors based on the spawn character.
*/
void	set_angle(t_player *player, char c)
{
	if (c == 'N' || c == 'S')
		set_ns_angle(player, c);
	else if (c == 'E' || c == 'W')
		set_ew_angle(player, c);
}
