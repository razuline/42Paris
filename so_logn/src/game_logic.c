/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_logic.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erazumov <erazumov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 20:49:38 by erazumov          #+#    #+#             */
/*   Updated: 2025/04/17 21:01:00 by erazumov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	exit_game(t_game *game, int exit_code);

void	collect_item(t_game *game, int x, int y)
{
	game->collect_curr--;
	game->map.grid[y][x] = FLOOR;
	ft_printf("Item collected! Remaining: %d\n", game->collect_curr);
	if (game->collect_curr == 0)
	{
		game->exit_access = 1;
		ft_printf("All items collected! The exit is now open!\n");
	}
}

void	win_game(t_game *game)
{
	ft_printf("------------------------------\n");
	ft_printf("       CONGRATULATIONS!       \n");
	ft_printf(" You escaped in %d moves!\n", game->moves);
	ft_printf("------------------------------\n");
	exit_game(game, EXIT_SUCCESS);
}

void	check_exit(t_game *game, int x, int y)
{
	(void)x;
	(void)y;

	if (game->exit_access == 1)
		win_game(game);
	else
		ft_printf("Exit is closed. Collect all items first!\n");

}
