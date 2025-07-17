/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   permutations.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erazumov <erazumov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/15 14:00:26 by erazumov          #+#    #+#             */
/*   Updated: 2025/07/17 16:02:58 by erazumov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PERMUTATIONS_H
# define PERMUTATIONS_H

#include <unistd.h>
#include <stdlib.h>

int		ft_strlen(char *str);
void	ft_putstr(char *str);
void	ft_swap(char *a, char *b);
void	sort_str(char *str, int len);
int		next_permutation(char *str, int len);

#endif
