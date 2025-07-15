/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   n_queens.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erazumov <erazumov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/15 13:53:05 by erazumov          #+#    #+#             */
/*   Updated: 2025/07/15 13:57:02 by erazumov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef N_QUEENS_H
# define N_QUEENS_H

#include <stdlib.h>
#include <unistd.h>

int		is_safe(int row, int col, int *board);
void	print_solution(int n, int *board);
void	solve_n_queens(int col, int n, int *board);

#endif
