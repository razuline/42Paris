/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   powerset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erazumov <erazumov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/13 15:32:10 by erazumov          #+#    #+#             */
/*   Updated: 2025/07/18 19:01:26 by erazumov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/** Le terme mathématique pour "powerset" (l'ensemble de toutes les parties
 * d'un ensemble).
 * Concernant l'exercice que nous avons fait, le sujet était de trouver
 * les sous-ensembles dont la somme correspond à un nombre cible.
 */

#include "powerset.h"

// Affiche les éléments d'un sous-ensemble
void	print_subset(int *subset, int size)
{
	int	i;

	i = 0;
	while (i < size)
	{
		printf("%d", subset[i]);
		if (i < size - 1)
			printf(" ");
		i++;
	}
	printf("\n");
}

// Fonction récursive pour trouver et afficher les sous-ensembles valides
void	find_subsets(int *nums, int num_count, int target, int *subset,
		int subset_size, int sum, int start_idx, int *solution)
{
	if (start_idx == num_count)
	{
		if (sum == target)
		{
			if (subset_size > 0)
			{
				print_subset(subset, subset_size);
				*solution = 1;
			}
		}
		return ;
	}
	find_subsets(nums, num_count, target, subset, subset_size, sum,
		start_idx + 1, solution);
	subset[subset_size] = nums[start_idx];
	find_subsets(nums, num_count, target, subset, subset_size + 1,
		sum + nums[start_idx], start_idx + 1, solution);
}

int	main(int ac, char **av)
{
	int	i;
	int	target;
	int	num_count;
	int *nums;
	int	*subset;
	int	solution;

	if (ac < 2)
		return (0);
	target = atoi(av[1]);
	num_count = ac - 2;
	nums = malloc(sizeof(int) * num_count);
	if (!nums)
		return (1);
	i = 0;
	while (i < num_count)
	{
		nums[i] = atoi(av[i + 2]);
		i++;
	}
	subset = malloc(sizeof(int) * num_count);
	if (!subset)
	{
		free(nums);
		return (1);
	}
	solution = 0;
	find_subsets(nums, num_count, target, subset, 0, 0, 0, &solution);
	if (target == 0 && !solution)
		printf("\n");
	free(nums);
	free(subset);
	return (0);
}
