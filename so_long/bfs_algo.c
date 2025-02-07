/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bfs_algo.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erazumov <erazumov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 17:17:26 by erazumov          #+#    #+#             */
/*   Updated: 2025/02/07 18:24:02 by erazumov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>
#include <stdlib.h>
#include <unistd.h>
/* Starting point P = {1, 1} */
int	directions[4][2] = {
	{-1, 0}, /* up */
	{1, 0}, /* down */
	{0, -1}, /* left */
	{0, 1} /* right */
};

typedef struct s_cell
{
	int	x;
	int	y;
}	t_cell;

bool	**make_visited(int height, int width)
{
	bool	**visited;
	int		i;
	int		j;

	i = 0;
	visited = (bool **)malloc(sizeof(bool *) * height); /* memory for rows */
	while (i < height)
	{
		visited[i] = (bool *)malloc(sizeof(bool) * width); /* memory for columns */
		j = 0;
		while (j < width)
		{
			visited[i][j] = false;
			j++;
		}
		i++;
	}
	return (visited);
}

bool	valid_direction(int x, int y, int height, int width, char **map)
{
	if (x < 0 || x >= height || y < 0 || y >= width)
	{
		return (false);
	}

	if (map[x][y] == '1')
	{
		return (false);
	}
	return (true);
}

void	bfs(char **map, int x, int y, int height, int width)
{
	bool	**visited;
}
