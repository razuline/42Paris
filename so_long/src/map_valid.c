/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_valid.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erazumov <erazumov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 18:16:34 by erazumov          #+#    #+#             */
/*   Updated: 2025/04/18 11:28:00 by erazumov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int		check_horiz_walls(t_game *game);
int		check_vert_walls(t_game *game);
int		is_valid_char(char c);
void	update_counts(char c, t_game *game, int x, int y, int counts[3]);
int		final_count_check(t_game *game, int counts[3]);

static int	check_rectang(t_game *game)
{
	int	y;
	int	curr_width;

	y = 1;
	while (y < game->map.height)
	{
		curr_width = ft_strlen(game->map.grid[y]);
		if (curr_width != game->map.width)
		{
			print_error("Map is not rectangular.");
			return (0);
		}
		y++;
	}
	return (1);
}

static int	check_walls(t_game *game)
{
	if (!check_horiz_walls(game))
	{
		print_error("Map is not enclosed by walls (top or bottom).");
		return (0);
	}
	if (!check_vert_walls(game))
	{
		print_error("Map is not enclosed by walls (left or right).");
		return (0);
	}
	return (1);
}

static int	process_char(t_game *game, int x, int y, int counts[3])
{
	char	curr_char;

	curr_char = game->map.grid[y][x];
	if (!is_valid_char(curr_char))
	{
		print_error("Invalid character found in map.");
		return (0);
	}
	update_counts(curr_char, game, x, y, counts);
	return (1);
}

static int	check_chars_and_count(t_game *game)
{
	int	x;
	int	y;
	int	counts[3]; // 0:P, 1:E, 2:C
	int	process_status;

	counts[0] = 0;
	counts[1] = 0;
	counts[2] = 0;
	y = 0;
	while (y < game->map.height)
	{
		x = 0;
		while (x < game->map.width)
		{
			process_status = process_char(game, x, y, counts);
			if (process_status == 0)
				return (0);
			x++;
		}
		y++;
	}
	if (!final_count_check(game, counts))
		return (0);
	return (1);
}

void	valid_map_struct(t_game *game)
{
	if (!check_rectang(game))
		exit_error(game, "Map validation failed: Not rectangular.");
	if (!check_walls(game))
		exit_error(game, "Map validation failed: Walls incomplete.");
	if (!check_chars_and_count(game))
		exit_error(game, "Map validation failed: Invalid characters or counts.");
	ft_printf("Map structure is valid.\n");
}
