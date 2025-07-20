/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   n_queens_bits.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erazumov <erazumov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/20 18:03:54 by erazumov          #+#    #+#             */
/*   Updated: 2025/07/20 18:32:06 by erazumov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef N_QUEENS_BITS_H
# define N_QUEENS_BITS_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

typedef unsigned long	mask;

void	disp(int *q, int n);
void	bt(int *q, int col, int n, mask rows, mask d1, mask d2);

#endif