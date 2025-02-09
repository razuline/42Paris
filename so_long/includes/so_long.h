/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erazumov <erazumov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/09 15:47:11 by erazumov          #+#    #+#             */
/*   Updated: 2025/02/09 15:56:14 by erazumov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
#define SO_LONG_H

# include <fcntl.h>
# include <stdbool.h>
# include <stdlib.h>
# include <unistd.h>
# include "libft.h"

typedef struct s_cell
{
	int	x;
	int	y;
}	t_cell;

typedef struct s_queue
{
	t_cell	*positions;
	int		front;
	int		rear;
	int		size;
}	t_queue;

/* Queue operations */
void	make_queue(t_queue *q, int max_size);
void	enqueue(t_queue *q, int x, int y);
bool	dequeue(t_queue *q, int *x, int *y);
bool	is_empty(t_queue *q);
void	free_queue(t_queue *q);

/* BFS Algorithm */
bool	bfs(char **map, int start_x, int start_y, int end_x, int end_y, int height, int width);

/* Map utilities */
bool	**make_visited(int height, int width);
void	free_visited(bool **visited, int height);
bool	is_valid(char **map, bool **visited, int x, int y, int height, int width);

/* Map handling */


#endif
