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
}	t_map;

int		min_of_three(int a, int b, int c);
void	solve_bsq(t_map *map);
int		parse_map(FILE *fp, t_map *map);
void	free_grid(t_map *map);
void	fill_and_print(t_map *map, int size, int row, int col);

#endif