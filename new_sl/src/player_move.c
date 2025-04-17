/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_move.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erazumov <erazumov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 20:34:50 by erazumov          #+#    #+#             */
/*   Updated: 2025/04/17 20:42:31 by erazumov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int		render_frame(t_game *game);
void	collect_item(t_game *game, int x, int y);
void	check_exit(t_game *game, int x, int y);

static int	is_valid_move(t_game *game, int next_x, int next_y)
{
	if (next_y < 0 || next_y >= game->map.height || \
		next_x < 0 || next_x >= game->map.width)
		return (0);
	if (game->map.grid[next_y][next_x] == WALL)
		return (0);
	return (1);
}

static void	upd_player_state(t_game *game, int next_x, int next_y)
{
	game->player_pos.x = next_x;
	game->player_pos.y = next_y;
	game->moves++;
	ft_printf("Moves: %d\n", game->moves);
	ft_putstr_fd("Moves: ", 1);
	ft_putnbr_fd(game->moves, 1);
	ft_putstr_fd("\n", 1);
	render_frame(game);
}

static void	target_cell(t_game *game, int next_x, int next_y)
{
	char	target_char;

	target_char = game->map.grid[next_y][next_x];
	if (target_char == COLLECTIBLE)
		collect_item(game, next_x, next_y);
	else if (target_char == EXIT)
		check_exit(game, next_x, next_y);
}

int	move_player(t_game *game, int dx, int dy)
{
	int	next_x;
	int	next_y;

	next_x = game->player_pos.x + dx;
	next_y = game->player_pos.y + dy;
	if (!is_valid_move(game, next_x, next_y))
		return (0);
	target_cell(game, next_x, next_y);
	upd_player_state(game, next_x, next_y);
	return (1);
}
