/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bfs_algo.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erazumov <erazumov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 17:17:26 by erazumov          #+#    #+#             */
/*   Updated: 2025/02/08 13:38:33 by erazumov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>
#include <stdlib.h>
#include <unistd.h>

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

bool	is_valid(char **map, int x, int y, int height, int width)
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

typedef struct s_queue
{
	t_cell	*positions;
	int		front;
	int		rear;
	int		size;
}	t_queue;

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

void	free_queue(t_queue *q)
{
	free(q->positions);
}

bool	bfs(char **map, int start_x, int start_y, int end_x, int end_y, int height, int width)
{
	bool	**visited;
	int		directions[4][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}}; /* up, down, left, right */
	t_queue	queue;
	/* Starting point P = {1, 1} */
	visited = make_visited(height, width);

}
