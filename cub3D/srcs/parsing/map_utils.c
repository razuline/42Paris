/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erazumov <erazumov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/06 20:07:02 by erazumov          #+#    #+#             */
/*   Updated: 2026/01/06 20:10:56 by erazumov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/*
** Fills a string with spaces and null-terminates it.
** Helps creating a uniform grid for the DDA algorithm.
*/
void	fill_with_spaces(char *str, int start, int end)
{
	while (start < end)
	{
		str[start] = ' ';
		start++;
	}
	str[start] = '\0';
}

/*
** Normalises a map line to game->map.width by padding with spaces.
** This prevents DDA from accessing out-of-bounds memory.
*/
char	*normalise_line(char *content, int max_width)
{
	char	*new_line;
	int		content_len;

	new_line = malloc(sizeof(char) * (max_width + 1));
	if (!new_line)
		return (NULL);
	content_len = ft_strlen(content);
	ft_memcpy(new_line, content, content_len);
	fill_with_spaces(new_line, content_len, max_width);
	return (new_line);
}

/*
** Allocates memory for the 2D grid and the line length tracking array.
** Initialises the grid with NULL to ensure safe cleaning in case of error.
*/
int	alloc_map_arrays(t_game *game)
{
	game->map.grid = ft_calloc(game->map.height + 1, sizeof(char *));
	if (!game->map.grid)
		return (0);
	game->map.line_len = malloc(sizeof(int) * game->map.height);
	if (!game->map.line_len)
	{
		free(game->map.grid);
		game->map.grid = NULL;
		return (0);
	}
	return (1);
}
