/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bsq_exam.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erazumov <erazumov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/16 15:55:08 by erazumov          #+#    #+#             */
/*   Updated: 2026/05/16 16:15:44 by erazumov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bsq.h"

void	solve_bsq(FILE *stream)
{
	t_map	m;
	char	*line = NULL;
	size_t	len = 0;

	if (fscanf(stream, "%d %c %c %c\n",
			   &m.rows,
			   &m.empty,
			   &m.obs,
			   &m.full) != 4)
	{
		fprintf(stderr, "map error\n");
		return ;
	}

	if (m.empty == m.obs ||
		m.empty == m.full ||
		m.obs == m.full)
	{
		fprintf(stderr, "map error\n");
		return ;
	}

	if (getline(&line, &len, stream) == -1)
	{
		fprintf(stderr, "map error\n");
		free(line);
		return ;
	}
	m.cols = 0;
	while (line[m.cols] && line[m.cols] != '\n')
		m.cols++;

	char	**map = malloc(sizeof(char *) * m.rows);
	int		**dp = malloc(sizeof(int *) * m.rows);
	int		max_size = 0;
	int		max_r = 0;
	int		max_c = 0;

	for (int r = 0; r < m.rows; ++r)
	{
		if (r > 0 && getline(&line, &len, stream) == -1)
		{
			fprintf(stderr, "map error\n");
			free_memory(map, dp, r);
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
		}

}