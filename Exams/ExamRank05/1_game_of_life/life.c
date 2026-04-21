/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   life.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erazumov <erazumov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/21 17:53:06 by erazumov          #+#    #+#             */
/*   Updated: 2026/04/21 18:09:20 by erazumov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct s_life
{
	int		width;
	int		height;
	int		iter;
	char	*board;
	char	*next;
}	t_life;

/**
 * Counts alive neighbors for a specific cell at (x, y)
 * Cells outside the board are considered dead (0)
 */
int	count_neighbors(t_life *l, int x, int y)
{
	int	count = 0;

	for (int i = -1; i <= 1; i++)
	{
		for (int j = -1; j <= 1; j++)
		{
			if (i == 0 && j == 0)
				continue;

			int	nx = x + j;
			int	ny = y + i;

			if (nx >= 0 && nx < l->width && ny >= 0 && ny < l->height)
			{
				if (l->board[ny * l->width + nx])
					count++;
			}
		}
	}
	return (count);
}

/**
 * Executes one iteration of Conway's Game of Life rules
 */
void	step(t_life *l)
{
	for (int y = 0; y < l->height; y++)
	{
		for (int x = 0; x < l->width; x++)
		{
			int	neighbors = count_neighbors(l, x, y);
			int	idx = y * l->width + x;

			if (l->board[idx])
				l->next[idx] = (neighbors == 2 || neighbors == 3);
			else
				l->next[idx] = (neighbors == 3);
		}
	}
	// Copy the next state back to the current board
	for (int i = 0; i < l->width * l->height; i++)
		l->board[i] = l->next[i];
}

int	main(int ac, char **av)
{
	if (ac != 4)
		return (1);

	t_life	l;
	l.width = atoi(av[1]);
	l.height = atoi(av[2]);
	l.iter = atoi(av[3]);

	// Initialise boards with 0 (dead cells)
	l.board = calloc(l.width * l.height, sizeof(char));
	l.next = calloc(l.width * l.height, sizeof(char));
	if (!l.board || !l.next)
		return (1);

	// Initial pen position and state
	int		px = 0;
	int		py = 0;
	int		pen_down = 0;
	char	cmd;

	// Process drawing commands from standard input
	while (read(0, &cmd, 1) > 0)
	{
		if (cmd == 'w' && py > 0)
			py--;
		else if (cmd == 's' && py < l.height - 1)
			py++;
		else if (cmd == 'a' && px > 0)
			px--;
		else if (cmd == 'd' && px < l.width - 1)
			px++;
		else if (cmd == 'x')
			pen_down = !pen_down;

		// If the pen is lowered, mark the cell as alive
		if (pen_down)
			l.board[py * l.width + px] = 1;
	}

	// Run the simulation for the specified number of iterations
	for (int i = 0; i < l.iter; i++)
		step(&l);

	// Output the final board state
	for (int y = 0; y < l.height; y++)
	{
		for (int x = 0; x < l.width; x++)
		{
			if (l.board[y * l.width + x])
				putchar('0');
			else
				putchar(' ');
		}
		putchar('\n');
	}

	// Cleanup
	free(l.board);
	free(l.next);
	return (0);
}
