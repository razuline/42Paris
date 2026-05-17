/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   life.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erazumov <erazumov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/21 17:53:06 by erazumov          #+#    #+#             */
/*   Updated: 2026/05/17 13:21:45 by erazumov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

/**
 * Counts alive neighbors for a specific cell at (x, y)
 * Cells outside the board are considered dead (0)
 */
int	count_neighbors(char *board, int w, int h, int x, int y)
{
	int	count = 0;

	for (int i = -1; i <= 1; ++i)
	{
		for (int j = -1; j <= 1; ++j)
		{
			if (i == 0 && j == 0)
				continue ;

			int	nx = x + j;
			int	ny = y + i;

			if (nx >= 0 && nx < w &&
				ny >= 0 && ny < h &&
				board[ny * w + nx])
			{
					count++;
			}
		}
	}
	return (count);
}

// 2. SIMULATE ONE STEP
void	step(char *board, char *next, int w, int h)
{
	for (int y = 0; y < h; ++y)
	{
		for (int x = 0; x < w; ++x)
		{
			int	neighbors = count_neighbors(board, w, h, x, y);
			int	idx = y * w + x;

			if (board[idx])
				next[idx] = (neighbors == 2 || neighbors == 3);
			else
				next[idx] = (neighbors == 3);
		}
	}
	// Copy the next state back to current board
	for (int i = 0; i < w * h; ++i)
		board[i] = next[i];
}

int	main(int ac, char **av)
{
	if (ac != 4)
		return (1);

	int		w = atoi(av[1]);
	int		h = atoi(av[2]);
	int		iter = atoi(av[3]);

	char	*board = calloc(w * h, 1);
	char	*next = calloc(w * h, 1);

	if (!board || !next)
		return (1);

	// Initial pen position and state
	int		px = 0;
	int		py = 0;
	int		pen = 0;
	char	cmd;

	// Process input commands
	while (read(0, &cmd, 1) > 0)
	{
		if (cmd == 'w' && py > 0)
			py--;
		if (cmd == 's' && py < h - 1)
			py++;
		if (cmd == 'a' && px > 0)
			px--;
		if (cmd == 'd' && px < w - 1)
			px++;
		if (cmd == 'x')
			pen = !pen;

		if (pen)
			board[py * w + px] = 1;
	}

	// Run generations
	for (int i = 0; i < iter; ++i)
		step(board, next, w, h);

	// Print final board
	for (int y = 0; y < h; ++y)
	{
		for (int x = 0; x < w; ++x)
		{
			if (board[y * w + x])
				putchar('0'); // Alive cell
			else
				putchar(' '); // Dead cell
		}
		putchar('\n');
	}

	free(board);
	free(next);

	return (0);
}
