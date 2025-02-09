/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bfs_algo.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erazumov <erazumov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 17:17:26 by erazumov          #+#    #+#             */
/*   Updated: 2025/02/09 15:59:25 by erazumov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "so_long.h"

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

bool	is_valid(char **map, bool **visited, int x, int y, int height, int width)
{
	if (x < 0 || x >= height || y < 0 || y >= width) /* Out of bounds */
	{
		return (false);
	}

	if (map[x][y] == '1') /* Wall */
	{
		return (false);
	}
	return (!visited[x][y]); /* Not visited */
}

void	make_queue(t_queue *q, int max_size)
{
	q->positions = (t_cell *)malloc(sizeof(t_cell) * max_size);
	q->front = q->rear = 0;
	q->size = max_size;
}

void	enqueue(t_queue *q, int x, int y)
{
	q->positions[q->rear].x = x;
	q->positions[q->rear].y = y;
	q->rear = (q->rear + 1) % q->size;
}

bool	dequeue(t_queue *q, int *x, int *y)
{
	if (q->front == q->rear)
		return (false); /* Queue is empty */
	*x = q->positions[q->front].x;
	*y = q->positions[q->front].y;
	q->front = (q->front + 1) % q->size;
	return (true);
}

bool	is_empty(t_queue *q)
{
	return (q->front == q->rear);
}

void	free_visited(bool **visited, int height)
{
	int	i;

	i = 0;
	while (i < height)
	{
		free(visited[i]);
		i++;
	}
	free(visited);
}

void	free_queue(t_queue *q)
{
	free(q->positions);
}

bool	bfs(char **map, int start_x, int start_y, int end_x, int end_y, int height, int width)
{
	bool	**visited;
	int		directions[4][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}}; /* up, down, left, right */
	t_queue	queue;
	int		x;
	int		y;
	int		new_x;
	int		new_y;
	int		dir;

	visited = make_visited(height, width);
	enqueue(&queue, start_x, start_y); /* Starting point */
	visited[start_x][start_y] = true; /* Mark starting point like visited */

	while (!is_empty(&queue))
	{
		dequeue(&queue, &x, &y); /* Extract current cell from queue */
		if (x == end_x && y == end_y) /* If the goal is achieved */
		{
			free_queue(&queue);
			free_visited(visited, height); /* Free all memory */
			return (true);
		}
		dir = 0;
		while (dir < 4)
		{
			new_x = x + directions[dir][1];
			new_y = y + directions[dir][0];
			if (is_valid(map, visited, new_x, new_y, height, width))
			{
				visited[new_x][new_y] = true;
				enqueue(&queue, new_x, new_y);
			}
			dir++;
		}
	}
	free_queue(&queue);
	free_visited(visited, height);
	return (false); /* No path found */
}
