/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   n_queens.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erazumov <erazumov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/15 13:53:05 by erazumov          #+#    #+#             */
/*   Updated: 2025/07/17 13:04:46 by erazumov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef N_QUEENS_H
# define N_QUEENS_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void	print_solution(int *board, int n);
int		is_safe(int *board, int row, int col);
void	solve_nqueens(int *board, int col, int n);

#endif
