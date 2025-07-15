/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   permutations.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erazumov <erazumov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/15 14:00:26 by erazumov          #+#    #+#             */
/*   Updated: 2025/07/15 14:17:54 by erazumov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PERMUTATIONS_H
# define PERMUTATIONS_H

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

int		ft_strlen(char *str);
void	ft_swap(char *a, char *b);
void	sort_str(char *str);
void	find_permutations(char *orig_str, char *curr_perm, int *used,
			int k, int len);

#endif
