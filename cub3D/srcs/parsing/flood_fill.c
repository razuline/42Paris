/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flood_fill.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erazumov <erazumov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/22 16:52:38 by erazumov          #+#    #+#             */
/*   Updated: 2026/01/06 17:33:14 by erazumov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/*
** Validates a single cell during flood fill traversal.
** Returns -1 if out of bounds or hit empty space (' ') - signals map is OPEN.
** Returns 0 if wall ('1') or already visited ('V') - skip this cell.
** Returns 1 if valid floor or player position - mark as visited and continue.
*/
static int	check_cell(char **map, int x, int y, int height)
{
	if (y < 0 || y >= height || x < 0 || !map[y] || x >= (int)ft_strlen(map[y]))
		return (-1);
	if (map[y][x] == '1' || map[y][x] == 'V')
		return (0);
	if (map[y][x] == ' ')
		return (-1);
	return (1);
}

/*
** Helper: Pushes 4 neighboring cells onto the stack for traversal.
** Ensures stack pointer does not exceed bounds before incrementing.
*/
static void	push_neighbors(int stack[10000][2], int *sp, int x, int y)
{
	if (*sp < 9996)
	{
		stack[*sp][0] = x;
		stack[(*sp)++][1] = y - 1;
		stack[*sp][0] = x;
		stack[(*sp)++][1] = y + 1;
		stack[*sp][0] = x - 1;
		stack[(*sp)++][1] = y;
		stack[*sp][0] = x + 1;
		stack[(*sp)++][1] = y;
	}
}

/*
** Iterative flood fill algorithm using a fixed-size stack to avoid overflow.
** Returns 0 if the fill reaches the map boundary or void space.
** Returns 1 if the area is completely enclosed by walls.
*/
int	flood_fill_iter(char **map, int start_x, int start_y, int height)
{
	int	stack[10000][2];
	int	sp;
	int	x;
	int	y;
	int	check;

	sp = 0;
	stack[sp][0] = start_x;
	stack[sp++][1] = start_y;
	while (sp > 0)
	{
		sp--;
		x = stack[sp][0];
		y = stack[sp][1];
		check = check_cell(map, x, y, height);
		if (check == -1)
			return (0);
		if (check == 0)
			continue ;
		map[y][x] = 'V';
		push_neighbors(stack, &sp, x, y);
	}
	return (1);
}
