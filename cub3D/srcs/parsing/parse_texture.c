/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_texture.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mayoucha <mayoucha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/12 12:24:06 by erazumov          #+#    #+#             */
/*   Updated: 2026/01/11 18:16:48 by mayoucha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/*
** Checks if file exists and has valid .xpm extension.
** Returns 1 if valid, 0 otherwise.
*/
static int	is_file_valid(char *path)
{
	int	fd;
	int	len;

	len = ft_strlen(path);
	if (len < 4 || ft_strncmp(path + len - 4, ".xpm", 4))
	{
		ft_putstr_fd("Error\nTexture must be a .xpm file\n", 2);
		return (0);
	}
	fd = open(path, O_RDONLY);
	if (fd < 0)
	{
		ft_putstr_fd("Error\nTexture file not found or unreadable\n", 2);
		return (0);
	}
	close(fd);
	return (1);
}

/*
** Validate texture line format (ID PATH).
*/
static int	is_valid_texture(char **tex)
{
	if (count_elem(tex) != 2)
	{
		ft_putstr_fd("Error\nInvalid texture line format\n", 2);
		return (0);
	}
	return (is_file_valid(tex[1]));
}

/*
** Store texture file path in appropriate array index (0=NO, 1=SO, 2=WE, 3=EA).
** Returns 1 on success, 0 on duplicate or failure.
*/
static int	copy_path(t_game *game, char **words)
{
	char	**target;

	target = NULL;
	if (!ft_strncmp(words[0], "NO", 3))
		target = &game->map.no_path;
	else if (!ft_strncmp(words[0], "SO", 3))
		target = &game->map.so_path;
	else if (!ft_strncmp(words[0], "WE", 3))
		target = &game->map.we_path;
	else if (!ft_strncmp(words[0], "EA", 3))
		target = &game->map.ea_path;
	if (!target)
		return (0);
	if (*target != NULL)
	{
		ft_putstr_fd("Error\nDuplicate texture\n", 2);
		return (0);
	}
	*target = ft_strdup(words[1]);
	return (*target != NULL);
}

/*
** Main function to parse texture line.
*/
int	parse_texture(t_game *game, char *line)
{
	char	**words;
	int		ret;

	replace_tabs(line);
	words = ft_split(line, ' ');
	if (!words)
		return (0);
	if (!words[0])
	{
		free_tab(words);
		return (1);
	}
	if (!is_valid_texture(words))
	{
		free_tab(words);
		return (0);
	}
	ret = copy_path(game, words);
	free_tab(words);
	return (ret);
}
