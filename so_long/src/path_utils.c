/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erazumov <erazumov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 16:26:46 by erazumov          #+#    #+#             */
/*   Updated: 2025/04/21 16:44:26 by erazumov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	is_valid_cell(char **grid, t_point size, t_point current)
{
	if (current.y < 0 || current.y >= size.y || \
		current.x < 0 || current.x >= size.x)
		return (0);
	if (grid[current.y][current.x] == WALL || \
		grid[current.y][current.x] == 'F')
		return (0);
	return (1);
}

int	is_reach(t_game *game, char **grid_copy)
{
	int		x;
	int		y;
	char	orig_char;

	y = 0;
	while (y < game->map.height)
	{
		x = 0;
		while (x < game->map.width)
		{
			orig_char = game->map.grid[y][x];
			if (orig_char == COLLECTIBLE || orig_char == EXIT)
			{
				if (grid_copy[y][x] != 'F')
					return (0);
			}
			x++;
		}
		y++;
	}
	return (1);
}
