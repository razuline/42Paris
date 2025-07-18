/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   powerset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erazumov <erazumov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/13 15:32:10 by erazumov          #+#    #+#             */
/*   Updated: 2025/07/17 21:40:57 by erazumov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "powerset.h"

int	*g_nums;
int	*g_subset;
int	g_target;
int	g_nums_size;

// Affiche les éléments d'un sous-ensemble
void	print_result(int size)
{
	int	i;

	i = 0;
	while (i < size)
	{
		printf("%d", g_subset[i]);
		if (i < size - 1)
			printf(" ");
		i++;
	}
	printf("\n");
}

// Fonction récursive pour trouver et afficher les sous-ensembles valides
void	find_subsets(int pos, int sum, int start)
{
	int	i;

	if (sum == g_target && pos > 0)
		print_result(pos);
	i = start;
	while (i < g_nums_size)
	{
		if (sum + g_nums[i] > g_target)
			continue ;
		g_subset[pos] = g_nums[i];
		find_subsets(pos + 1, sum + g_nums[i], i + 1);
	}
}

int	main(int ac, char **av)
{
	int	i;

	if (ac < 2)
	{
		printf("\n");
		return (0);
	}
	g_target = atoi(av[1]);
	g_nums_size = ac - 2;
	g_nums = malloc(sizeof(int) * g_nums_size);
	g_subset = malloc(sizeof(int) * g_nums_size);
	if (!g_nums || !g_subset)
	{
		free(g_nums);
		free(g_subset);
		return (1);
	}
	i = 0;
	while (i < g_nums_size)
	{
		g_nums[i] = atoi(av[i + 2]);
		i++;
	}
	find_subsets(0, 0, 0);
	free(g_nums);
	free(g_subset);
	return (0);
}
