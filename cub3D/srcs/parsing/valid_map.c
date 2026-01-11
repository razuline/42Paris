/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   valid_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erazumov <erazumov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/23 19:18:10 by erazumov          #+#    #+#             */
/*   Updated: 2026/01/06 19:45:55 by erazumov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/*
** Verifies that all characters in grid are allowed (0, 1, N, S, E, W, space).
** Returns 0 and prints an error if an invalid character is found.
*/
int	valid_chars(t_game *game)
{
	int	x;
	int	y;

	y = 0;
	while (game->map.grid[y])
	{
		x = 0;
		while (game->map.grid[y][x])
		{
			if (!is_valid_char(game->map.grid[y][x]))
			{
				ft_putstr_fd("Error\nInvalid character in map\n", 2);
				return (0);
			}
			x++;
		}
		y++;
	}
	return (1);
}

/*
** Creates a deep copy of the map grid for the flood fill validation.
** Each row is duplicated using ft_strdup.
*/
static char	**duplicate_map(t_game *game)
{
	int		y;
	char	**copy;

	if (!game || !(game->map.height))
		return (NULL);
	copy = ft_calloc(game->map.height + 1, sizeof(char *));
	if (!copy)
		return (NULL);
	y = 0;
	while (game->map.grid[y])
	{
		copy[y] = ft_strdup(game->map.grid[y]);
		if (!copy[y])
		{
			free_tab(copy);
			return (NULL);
		}
		y++;
	}
	return (copy);
}

/*
** Runs the enclosure check using a map copy.
** If the player can reach the void or boundaries, returns 0.
*/
int	check_map_closed(t_game *game)
{
	char	**copy;
	int		result;

	copy = duplicate_map(game);
	if (!copy)
	{
		ft_putstr_fd("Error\nMalloc failed during map validation\n", 2);
		return (0);
	}
	result = flood_fill_iter(copy, (int)game->player.pos.x,
			(int)game->player.pos.y, game->map.height);
	free_tab(copy);
	if (!result)
		ft_putstr_fd("Error\nMap is not enclosed by walls\n", 2);
	return (result);
}
