/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   powerset.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erazumov <erazumov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/13 15:32:18 by erazumov          #+#    #+#             */
/*   Updated: 2025/07/18 18:57:25 by erazumov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef POWERSET_H
# define POWERSET_H

#include <stdio.h>
#include <stdlib.h>

void	print_subset(int *subset, int size);
void	find_subsets(int *nums, int num_count, int target, int *subset,
			int subset_size, int sum, int start_idx, int *solution);

#endif
