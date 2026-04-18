/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erazumov <erazumov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/18 16:00:32 by erazumov          #+#    #+#             */
/*   Updated: 2026/04/18 16:25:18 by erazumov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bsq.h"

/**
 * Core logic for processing a single map source
 */
void	process_map(FILE *fp)
{
	t_map	map;

	if (!parse_map(fp, &map))
		return ;

	solve_bsq(&map);
	free_grid(&map);
}

int	main(int ac, char **av)
{
	int		i;
	FILE	*fp;

	// Case 1: Standard Input
	if (ac == 1)
	{
		process_map(stdin);
	}
	// Case 2: Multiple Files
	else
	{
		for (i = 1; i < ac; i++)
		{
			fp = fopen(av[i], "r");
			if (fp == NULL)
			{
				fprintf(stderr, "map error\n");
			}
			else
			{
				process_map(fp);
				fclose(fp);
			}

			/* * IMPORTANT: Add a newline between maps.
			 * Prints it only if it's NOT the last file.
			 */
			if (i < ac - 1)
			{
				printf("\n");
			}
		}
	}
	return (0);
}
