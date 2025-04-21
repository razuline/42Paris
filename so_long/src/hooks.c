/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erazumov <erazumov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 20:29:13 by erazumov          #+#    #+#             */
/*   Updated: 2025/04/21 14:11:56 by erazumov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static int	window_close(t_game *game)
{
	exit_game(game, EXIT_SUCCESS);
	return (0);
}

static int	keypress(int keycode, t_game *game)
{
	int	moved;

	moved = 0;
	if (keycode == KEY_ESC)
		window_close(game);
	else if (keycode == KEY_W)
		moved = move_player(game, 0, -1);
	else if (keycode == KEY_A)
		moved = move_player(game, -1, 0);
	else if (keycode == KEY_S)
		moved = move_player(game, 0, 1);
	else if (keycode == KEY_D)
		moved = move_player(game, 1, 0);
	(void)moved;
	return (0);
}

void	setup_hooks(t_game *game)
{
	mlx_hook(game->win, 2, (1L << 0), keypress, game);
	mlx_hook(game->win, 17, 0, window_close, game);
	mlx_hook(game->win, 12, (1L << 15), render_frame, game);
}
