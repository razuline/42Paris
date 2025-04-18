/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_grid_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erazumov <erazumov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 18:33:14 by erazumov          #+#    #+#             */
/*   Updated: 2025/04/17 21:12:26 by erazumov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	copy_map_grid(t_game *game, char ***grid_copy_ptr)
{
	int		y;
	char	**new_grid;

	*grid_copy_ptr = NULL;
	new_grid = (char **)malloc(sizeof(char *) * (game->map.height + 1));
	if (!new_grid)
		return (-1);
	y = 0;
	while (y < game->map.height)
	{
		new_grid[y] = ft_strdup(game->map.grid[y]);
		if (!new_grid[y])
		{
			while (--y >= 0)
				free(new_grid[y]);
			free(new_grid);
			return (-1);
		}
		y++;
	}
	new_grid[y] = NULL;
	*grid_copy_ptr = new_grid;
	return (0);
}

void	free_grid_copy(char **grid_copy, int height)
{
	int	y;

	if (!grid_copy)
		return ;
	y = 0;
	while (y < height)
	{
		if (grid_copy[y])
			free(grid_copy[y]);
		y++;
	}
	free(grid_copy);
}
