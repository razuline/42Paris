/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   play.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erazumov <erazumov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 13:54:53 by erazumov          #+#    #+#             */
/*   Updated: 2025/03/21 14:20:26 by erazumov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "so_long.h"

int	move_player(int key, t_game *game)
{
	int	new_x;
	int	new_y;

	new_x = game->map.player_x;
	new_y = game->map.player_y;
	if (key == KEY_W) /* Up */
		new_y -= 1;
	else if (key == KEY_S) /* Down */
		new_y += 1;
	else if (key == KEY_A) /* Left */
		new_x -= 1;
	else if (key == KEY_D) /* Right */
		new_x += 1;
	else if (key == KEY_ESC) /* Esc */
		close_game(game);

	if (game->map.grid[new_y][new_x] != '1')
	{
		game->map.grid[game->map.player_y][game->map.player_x] = '0';
		game->map.grid[new_y][new_x] = 'P';
		game->map.player_x = new_x;
		game->map.player_y = new_y;
		render_game(game);
	}
	return (0);
}
