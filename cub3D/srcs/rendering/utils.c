/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erazumov <erazumov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/18 15:52:00 by mayoucha          #+#    #+#             */
/*   Updated: 2026/01/10 14:33:28 by erazumov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/*
** Connects window events (closing, key press, key release) to their handlers.
*/
int	init_hooks(t_game *game)
{
	mlx_hook(game->mlx_data->window, 17, 0, close_game, game);
	mlx_hook(game->mlx_data->window, 2, 1L << 0, key_press, game);
	mlx_hook(game->mlx_data->window, 3, 1L << 1, key_release, game);
	mlx_loop_hook(game->mlx_data->ptr_mlx, draw_loop, game);
	mlx_put_image_to_window(game->mlx_data->ptr_mlx,
		game->mlx_data->window, game->mlx_data->image, 0, 0);
	return (0);
}

/*
** Sets movement and rotation flags to true when keys are pressed.
*/
int	key_press(int keycode, t_game *game)
{
	if (keycode == KEY_ESC)
		close_game(game);
	if (keycode == KEY_W)
		game->player.key_up = 1;
	if (keycode == KEY_S)
		game->player.key_down = 1;
	if (keycode == KEY_A)
		game->player.key_left = 1;
	if (keycode == KEY_D)
		game->player.key_right = 1;
	if (keycode == KEY_LEFT)
		game->player.left_rotate = 1;
	if (keycode == KEY_RIGHT)
		game->player.right_rotate = 1;
	return (1);
}

/*
** Sets movement and rotation flags to false when keys are released.
*/
int	key_release(int keycode, t_game *game)
{
	if (keycode == KEY_W)
		game->player.key_up = 0;
	if (keycode == KEY_S)
		game->player.key_down = 0;
	if (keycode == KEY_A)
		game->player.key_left = 0;
	if (keycode == KEY_D)
		game->player.key_right = 0;
	if (keycode == KEY_LEFT)
		game->player.left_rotate = 0;
	if (keycode == KEY_RIGHT)
		game->player.right_rotate = 0;
	return (1);
}

/*
** Converts separate RGB values into a single integer for MLX colors.
*/
int	rgb_to_int(t_color color)
{
	return (color.r << 16 | color.g << 8 | color.b);
}
