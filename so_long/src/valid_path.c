/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   valid_path.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erazumov <erazumov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 21:03:04 by erazumov          #+#    #+#             */
/*   Updated: 2025/04/21 16:57:59 by erazumov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static int	process_neighbors(t_stack *stack, char **grid, t_point size,
								t_point current)
{
	int			i;
	t_point		next;
	const int	g_dx[] = {1, -1, 0, 0};
	const int	g_dy[] = {0, 0, 1, -1};

	i = 0;
	while (i < 4)
	{
		next.x = current.x + g_dx[i];
		next.y = current.y + g_dy[i];
		if (is_valid_cell(grid, size, next))
		{
			grid[next.y][next.x] = 'F';
			if (!push(stack, next))
				return (0);
		}
		i++;
	}
	return (1);
}

static int	flood_fill_iter(char **grid_copy, t_point size, t_point start)
{
	t_stack	stack;
	t_point	current;
	int		status;

	init_stack(&stack);
	if (!is_valid_cell(grid_copy, size, start))
		return (1);
	if (!push(&stack, start))
		return (0);
	grid_copy[start.y][start.x] = 'F';
	status = 1;
	while (stack.top >= 0 && status == 1)
	{
		current = pop(&stack);
		status = process_neighbors(&stack, grid_copy, size, current);
	}
	return (status);
}

void	valid_path(t_game *game)
{
	t_point	map_size;
	int		is_reachable;
	int		fill_status;
	char	**grid_copy;

	grid_copy = NULL;
	if (copy_map_grid(game, &grid_copy) < 0)
		exit_error(game, "Memory allocation failed for map copy "
			"(path validation).");
	map_size.x = game->map.width;
	map_size.y = game->map.height;
	fill_status = flood_fill_iter(grid_copy, map_size, game->player_pos);
	is_reachable = 0;
	if (fill_status)
		is_reachable = is_reach(game, grid_copy);
	free_grid_copy(grid_copy, game->map.height);
	if (!fill_status)
		exit_error(game, "Flood fill failed (stack overflow?). "
			"Increase MAX_STACK_SIZE?");
	if (!is_reachable)
		exit_error(game, "Map has an invalid path: Not all collectibles "
			"or exit are reachable.");
	ft_printf("Map path is valid.\n");
}
