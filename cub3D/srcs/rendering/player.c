/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mayoucha <mayoucha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/04 20:27:29 by mayoucha          #+#    #+#             */
/*   Updated: 2026/01/10 17:49:29 by mayoucha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/*
** Rotates player direction and camera plane using rotation matrices.
*/
static void	rotate_player(t_game *game, double rot_speed)
{
	double	old_dir_x;
	double	old_plane_x;

	old_dir_x = game->player.dir_x;
	game->player.dir_x = game->player.dir_x * cos(rot_speed)
		- game->player.dir_y * sin(rot_speed);
	game->player.dir_y = old_dir_x * sin(rot_speed)
		+ game->player.dir_y * cos(rot_speed);
	old_plane_x = game->player.plane_x;
	game->player.plane_x = game->player.plane_x * cos(rot_speed)
		- game->player.plane_y * sin(rot_speed);
	game->player.plane_y = old_plane_x * sin(rot_speed)
		+ game->player.plane_y * cos(rot_speed);
}

/*
** Moves player forward/backward with basic collision checking.
*/
static void	move_forward_backward(t_player *player, t_game *game, float speed)
{
	float	new_x;
	float	new_y;

	if (player->key_up)
	{
		new_x = player->pos.x + player->dir_x * speed;
		new_y = player->pos.y + player->dir_y * speed;
		if (!touch(new_x, new_y, game))
		{
			player->pos.x = new_x;
			player->pos.y = new_y;
		}
	}
	if (player->key_down)
	{
		new_x = player->pos.x - player->dir_x * speed;
		new_y = player->pos.y - player->dir_y * speed;
		if (!touch(new_x, new_y, game))
		{
			player->pos.x = new_x;
			player->pos.y = new_y;
		}
	}
}

/*
** Moves player left/right (strafing) using perpendicular vector.
*/
static void	move_strafe(t_player *player, t_game *game, float speed)
{
	t_collision	data;

	data.perp_x = -player->dir_y;
	data.perp_y = player->dir_x;
	if (player->key_left)
	{
		data.new_x = player->pos.x - data.perp_x * speed;
		data.new_y = player->pos.y - data.perp_y * speed;
		if (!touch(data.new_x, data.new_y, game))
		{
			player->pos.x = data.new_x;
			player->pos.y = data.new_y;
		}
	}
	if (player->key_right)
	{
		data.new_x = player->pos.x + data.perp_x * speed;
		data.new_y = player->pos.y + data.perp_y * speed;
		if (!touch(data.new_x, data.new_y, game))
		{
			player->pos.x = data.new_x;
			player->pos.y = data.new_y;
		}
	}
}

/*
** Updates player orientation and position based on active keys.
*/
void	move_player(t_player *p, t_game *g)
{
	float	move_speed;
	double	rot_speed;

	move_speed = 0.1f;
	rot_speed = 0.05;
	move_forward_backward(p, g, move_speed);
	move_strafe(p, g, move_speed);
	if (p->left_rotate)
		rotate_player(g, -rot_speed);
	if (p->right_rotate)
		rotate_player(g, rot_speed);
}
