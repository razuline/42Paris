/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   powerset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erazumov <erazumov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/13 15:32:10 by erazumov          #+#    #+#             */
/*   Updated: 2025/07/15 16:16:52 by erazumov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "powerset.h"

/**
 * @brief Affiche les éléments d'un sous-ensemble
 */
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

/**
 * @brief Fonction récursive pour trouver et afficher les sous-ensembles valides
 * @param target La somme à atteindre
 * @param numbers L'ensemble des nombres d'entrée (non trié)
 * @param size Le nombre total d'éléments dans 'numbers'
 * @param start_index L'index à partir duquel commencer l'exploration
 * @param current_subset Le sous-ensemble en cours de construction
 * @param subset_size La taille actuelle de 'current_subset'
 */
void	find_subsets(int target, int *nums, int size, int idx,
	int *curr_subset, int subset_size, int *solution)
{
	int	i;
	int	curr_sum;

	// Cas de base : on a considéré tous les nombres
	if (idx == size)
	{
		// Une fois au bout, on calcule la somme du sous-ensemble qu'on a construit
		curr_sum = 0;
		i = 0;
		while (i < subset_size)
		{
			curr_sum += curr_subset[i];
			i++;
		}
		// Si la somme est égale à la cible, on affiche la solution
		if (curr_sum == target)
		{
			if (subset_size > 0)
			{
				print_subset(curr_subset, subset_size);
				*solution = 1;
			}
		}
		return ;
	}
	// -- Exploration par choix binaire --

	// Choix 1 : On IGNORE le nombre à l'index actuel et on continue l'exploration
	find_subsets(target, nums, size, idx + 1, curr_subset, subset_size, solution);

	// Choix 2 : On PREND le nombre à l'index actuel
	curr_subset[subset_size] = nums[idx];
	// Et on continue l'exploration avec ce nombre ajouté au "panier"
	find_subsets(target, nums, size, idx + 1, curr_subset, subset_size + 1, solution);
}

int	main(int ac, char **av)
{
	int	i;
	int	target;
	int	num_count;
	int	*nums;
	int	*curr_subset;
	int	solution;

	if (ac < 2)
		return (1);
	target = atoi(av[1]);
	num_count = ac - 2;
	if (num_count < 0) // Si il n'y a pas de nombres dans l'ensemble
		num_count = 0;

	// Allouer la mémoire et lire les nombres
	nums = malloc(sizeof(int) * num_count);
	curr_subset = malloc(sizeof(int) * num_count);
	if (!nums || !curr_subset)
		return (1);
	i = 0;
	while (i < num_count)
	{
		nums[i] = atoi(av[i + 2]);
		i++;
	}

	// 1. On initialise le flag à 0 (faux)
	solution = 0;
	// 2. On lance la recherche en passant l'ADRESSE du flag (&)
	find_subsets(target, nums, num_count, 0, curr_subset, 0, &solution);
	// 3. On applique la règle spéciale pour l'ensemble vide
	if (target == 0 && !solution)
		printf("\n");

	// Nettoyer
	free(nums);
	free(curr_subset);

	return (0);
}
