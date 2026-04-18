/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bsq.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erazumov <erazumov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/18 13:35:16 by erazumov          #+#    #+#             */
/*   Updated: 2026/04/18 16:29:32 by erazumov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BSQ_H
# define BSQ_H

# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <errno.h>

typedef struct s_map
{
	int		height;
	int		width;

	char	empty;
	char	obs;
	char	full;

	char	**grid;
}			t_map;

/* -------------------------------- PARSING --------------------------------- */

int		read_metadata(FILE *fp, t_map *map);
int		init_grid(FILE *fp, t_map *map);
int		load_lines(FILE *fp, t_map *map);
void	free_grid(t_map *map);
int		parse_map(FILE *fp, t_map *map);

/* ------------------------------- ALGORITHM -------------------------------- */

int		min_of_three(int a, int b, int c);
void	free_dp(int **dp, int height);
void	solve_bsq(t_map *map);
void	process_map(FILE *fp);

/* -------------------------------- DISPLAY --------------------------------- */

void	fill_and_print(t_map *map, int size, int row, int col);

#endif