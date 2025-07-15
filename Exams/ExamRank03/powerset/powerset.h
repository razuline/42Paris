/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   powerset.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erazumov <erazumov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/13 15:32:18 by erazumov          #+#    #+#             */
/*   Updated: 2025/07/15 16:18:16 by erazumov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef POWERSET_H
# define POWERSET_H

#include <stdio.h>
#include <stdlib.h>

void	print_subset(int *subset, int size);
void	find_subsets(int target, int *nums, int size, int idx,
			int *curr_subset, int subset_size, int *solution);

#endif
