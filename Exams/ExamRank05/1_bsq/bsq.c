/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bsq.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erazumov <erazumov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/14 16:28:36 by erazumov          #+#    #+#             */
/*   Updated: 2026/05/17 15:39:07 by erazumov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bsq.h"

int	min_val(int a, int b, int c)
{
	int	min = a;

	if (b < min)
		min = b;
	if (c < min)
		min = c;

	return (min);
}

int	valid_line(char *line, t_map *m)
{
	int	i = 0;

	// 1. Loop through characters until the end of the line
	while (line[i] && line[i] != '\n')
	{
		// Check: Is this character illegal?
		if (line[i] != m->empty && line[i] != m->obs)
			return (0); // Found a weird character -> Instant Fail!
		i++;
	}
	// 2. Check the size of the row
	if (i != m->cols)
		return (0); // The line is too short or too long -> Fail!

	return (1); // Clean line -> Pass!
}

void	free_memory(char **map, int **dp, int rows)
{
	// 1. Walk through every single row
	for (int i = 0; i < rows; ++i)
	{
		if (map)
			free(map[i]); // Free the character hallway at floor 'i'
		if (dp)
			free(dp[i]); // Free the integer hallway at floor 'i'
	}
	free(map);
	free(dp);
}

void	solve_bsq(FILE *stream)
{
	t_map	m;
	char	*line = NULL;
	size_t	len = 0;

	// 1. Header Parsing & Validation
	if (fscanf(stream, "%d %c %c %c\n",
			   &m.rows,
			   &m.empty,
			   &m.obs,
			   &m.full) != 4)
	{
		fprintf(stderr, "map error\n");
		return ;
	}

	// Check for duplicate characters
	if (m.empty == m.obs ||
		m.empty == m.full ||
		m.obs == m.full)
	{
		fprintf(stderr, "map error\n");
		return ;
	}

	// 2. Get Width from the First Line
	if (getline(&line, &len, stream) == -1)
	{
		fprintf(stderr, "map error\n");
		free(line);
		return ;
	}
	m.cols = 0;
	while (line[m.cols] && line[m.cols] != '\n')
		m.cols++;

	// 3. Allocate Memory & Trackers
	char	**map = malloc(sizeof(char *) * m.rows);
	int		**dp = malloc(sizeof(int *) * m.rows);
	int		max_size = 0;
	int		max_r = 0;
	int		max_c = 0;

	// 4. The Main Processing Loop (The Core Logic)
	for (int r = 0; r < m.rows; ++r)
	{
		if (r > 0 && getline(&line, &len, stream) == -1)
		{
			fprintf(stderr, "map error\n");
			free_memory(map, dp, r); // Free only what was allocated so far
			free(line);
			return ;
		}

		if (!valid_line(line, &m))
		{
			fprintf(stderr, "map error\n");
			free_memory(map, dp, r);
			free(line);
			return ;
		}

		map[r] = malloc(m.cols + 1);
		dp[r] = malloc(sizeof(int) * m.cols);

		for (int c = 0; c < m.cols; ++c)
		{
			map[r][c] = line[c];
			if (line[c] == m.obs)
				dp[r][c] = 0;
			else
			{
				if (r == 0 || c == 0)
					dp[r][c] = 1;
				else
					dp[r][c] = min_val(dp[r-1][c],
									   dp[r][c-1],
									   dp[r-1][c-1]) + 1;

				if (dp[r][c] > max_size)
				{
					max_size = dp[r][c];
					max_r = r;
					max_c = c;
				}
			}
		}
		map[r][m.cols] = '\0';
	}

	// 5. Drawing, Output & Cleanup
	for (int r = max_r - max_size + 1; r <= max_r; ++r)
	{
		for (int c = max_c - max_size + 1; c <= max_c; ++c)
			map[r][c] = m.full;
	}

	for (int r = 0; r < m.rows; ++r)
		fprintf(stdout, "%s\n", map[r]);

	free_memory(map, dp, m.rows);
	free(line);
}

int	main(int ac, char **av)
{
	if (ac == 1)
		solve_bsq(stdin);
	else
	{
		for (int i = 1; i < ac; ++i)
		{
			FILE	*fp = fopen(av[i], "r");

			if (!fp)
			{
				fprintf(stderr, "map error\n");
				continue ;
			}
			solve_bsq(fp);
			fclose(fp);

			if (i < ac - 1)
				fprintf(stdout, "\n");
		}
	}
	return (0);
}
