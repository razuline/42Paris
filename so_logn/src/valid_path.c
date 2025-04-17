/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   valid_path.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erazumov <erazumov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 21:03:04 by erazumov          #+#    #+#             */
/*   Updated: 2025/04/17 21:11:49 by erazumov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int		copy_map_grid(t_game *game, char ***grid_copy_ptr);
void	free_grid_copy(char **grid_copy, int height);

static int	is_valid_cell(char **grid, t_point size, t_point current)
{
	if (current.y < 0 || current.y >= size.y || \
		current.x < 0 || current.x >= size.x)
		return (0);
	if (grid[current.y][current.x] == WALL || \
		grid[current.y][current.x] == 'F')
		return (0);
	return (1);
}

static void	flood_fill(char **grid_copy, t_point size, t_point current)
{
	if (!is_valid_cell(grid_copy, size, current))
		return ;
	grid_copy[current.y][current.x] = 'F';
	flood_fill(grid_copy, size, (t_point){current.x + 1, current.y});
	flood_fill(grid_copy, size, (t_point){current.x - 1, current.y});
	flood_fill(grid_copy, size, (t_point){current.x, current.y + 1});
	flood_fill(grid_copy, size, (t_point){current.x, current.y - 1});
}

static int	is_reach(t_game *game, char **grid_copy)
{
	int	x;
	int	y;
	char orig_char;

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

void	valid_path(t_game *game)
{
	char	**grid_copy;
	t_point	map_size;
	int		is_reachable;

	if (copy_map_grid(game, &grid_copy) < 0)
		exit_error(game, "Memory allocation failed for map copy (path validation).");
	map_size.x = game->map.width;
	map_size.y = game->map.height;
	flood_fill(grid_copy, map_size, game->player_pos);
	is_reachable = is_reach(game, grid_copy);
	free_grid_copy(grid_copy, game->map.height);
	if (!is_reachable)
		exit_error(game, "Map has an invalid path: Not all collectibles or exit are reachable.");
	ft_printf("Map path is valid.\n");
}
