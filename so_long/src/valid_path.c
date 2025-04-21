/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   valid_path.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erazumov <erazumov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 21:03:04 by erazumov          #+#    #+#             */
/*   Updated: 2025/04/21 14:33:48 by erazumov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

#define MAX_STACK_SIZE (1024 * 10)

typedef struct s_stack
{
	t_point	coords[MAX_STACK_SIZE];
	int		top;
}			t_stack;

static void	init_stack(t_stack *stack)
{
	stack->top = -1;
}

static int	push(t_stack *stack, t_point p)
{
	if (stack->top >= MAX_STACK_SIZE - 1)
		return (0);
	stack->top++;
	stack->coords[stack->top] = p;
	return (1);
}

static t_point	pop(t_stack *stack)
{
	if (stack->top < 0)
		return ((t_point){-1, -1});
	return (stack->coords[stack->top--]);
}

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

static void	flood_fill_iter(char **grid_copy, t_point size, t_point start)
{
	t_stack	stack;
	t_point	current;
	t_point	next;
	int		dx[4] = {1, -1, 0, 0};
	int		dy[4] = {0, 0, 1, -1};
	int		i;

	init_stack(&stack);
	if (!is_valid_cell(grid_copy, size, start))
		return (1);
	if (!push(&stack, start))
		return (0);
	grid_copy[start.y][start.x] = 'F';
	while (stack.top >= 0)
	{
		current = pop(&stack);
		i = 0;
		while (i < 4)
		{
			next.x = current.x + dx[i];
			next.y = current.y + dy[i];
			if (is_valid_cell(grid_copy, size, next))
			{
				grid_copy[next.y][next.x] = 'F';
				if (!push(&stack, next))
					return (0);
			}
			i++;
		}
	}
	return (1);
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
	int		fill_status;

	grid_copy = NULL;
	if (copy_map_grid(game, &grid_copy) < 0)
		exit_error(game, "Memory allocation failed for map copy (path validation).");
	map_size.x = game->map.width;
	map_size.y = game->map.height;
	fill_status = flood_fill_iter(grid_copy, map_size, game->player_pos);
	if (fill_status == 0)
	{
		free_grid_copy(grid_copy, game->map.height);
		exit_error(game, "Flood fill failed (stack overflow?). Increase MAX_STACK_SIZE?");
	}
	is_reachable = is_reach(game, grid_copy);
	free_grid_copy(grid_copy, game->map.height);
	if (!is_reachable)
		exit_error(game, "Map has an invalid path: Not all collectibles or exit are reachable.");
	ft_printf("Map path is valid.\n");
}
