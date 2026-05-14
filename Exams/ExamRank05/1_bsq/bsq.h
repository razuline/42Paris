/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bsq.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erazumov <erazumov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/18 13:35:16 by erazumov          #+#    #+#             */
/*   Updated: 2026/05/14 17:10:15 by erazumov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BSQ_H
# define BSQ_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

typedef struct s_map
{
	int		rows;
	int		cols;
	char	empty;
	char	obs;
	char	full;
}	t_map;

int		min_val(int a, int b, int c);
int		valid_line(char *line, t_map *m);
void	free_memory(char **map, int **dp, int rows);
void	solve_bsq(FILE *stream);

#endif