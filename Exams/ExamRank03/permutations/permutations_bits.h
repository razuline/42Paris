/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   permutations_bits.h                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erazumov <erazumov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/20 19:54:02 by erazumov          #+#    #+#             */
/*   Updated: 2025/07/20 19:55:24 by erazumov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PERMUTATIONS_BITS_H
# define PERMUTATIONS_BITS_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int		ft_strlen(char *str);
void	ft_putstr(char *str);
void	ft_swap(char *a, char *b);
void	sort_str(char *str, int len);
int		next_permutation(char *str, int len);

#endif