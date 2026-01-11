/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mayoucha <mayoucha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/23 19:49:30 by erazumov          #+#    #+#             */
/*   Updated: 2026/01/11 18:19:43 by mayoucha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/*
** Checks if all 4 textures and 2 colors have been assigned.
** Returns 1 if the configuration is complete, 0 otherwise.
*/
static int	is_config_complete(t_game *game)
{
	if (!game->map.no_path || !game->map.so_path || !game->map.we_path
		|| !game->map.ea_path)
		return (0);
	if (game->map.floor_color == -1 || game->map.ceiling_color == -1)
		return (0);
	return (1);
}

/*
** Identifies if a line belongs to the map (starts with 0, 1, or player).
** Spaces are also considered valid map characters.
*/
static int	is_map_line(char *line)
{
	int	i;

	i = 0;
	while (line[i] && ft_isspace(line[i]))
		i++;
	if (!line[i])
		return (0);
	if (line[i] == '1' || line[i] == '0')
		return (1);
	if (ft_strchr("NSEW", line[i]))
	{
		if (line[i + 1] == ' ' || line[i + 1] == '0' || line[i + 1] == '1'
			|| line[i + 1] == '\0')
			return (1);
	}
	return (0);
}

/*
** Parses a single configuration line using identifiers.
*/
static int	parse_line(t_game *game, char *line)
{
	int		i;
	t_color	tmp;

	remove_newline(line);
	i = 0;
	while (line[i] && ft_isspace(line[i]))
		i++;
	if (line[i] == '\0')
		return (1);
	if (!ft_strncmp(&line[i], "NO", 2) || !ft_strncmp(&line[i], "SO", 2)
		|| !ft_strncmp(&line[i], "WE", 2) || !ft_strncmp(&line[i], "EA", 2))
		return (parse_texture(game, &line[i]));
	if ((line[i] == 'F' || line[i] == 'C') && ft_isspace(line[i + 1]))
	{
		tmp.r = -1;
		if (!parse_color(&tmp, &line[i]))
			return (0);
		if (line[i] == 'F')
			game->map.floor_color = (tmp.r << 16 | tmp.g << 8 | tmp.b);
		else
			game->map.ceiling_color = (tmp.r << 16 | tmp.g << 8 | tmp.b);
		return (1);
	}
	return (0);
}

/*
** Helper to handle the transition to map parsing to keep main loop short.
*/
static int	handle_map_entry(t_game *game, int fd, char *line)
{
	if (!is_config_complete(game))
	{
		ft_putstr_fd("Error\nConfig incomplete\n", 2);
		return (0);
	}
	return (parse_map(game, fd, line));
}

/*
** Main parsing loop. Reads .cub file and ensures map is the last element.
*/
int	parse_file(char *path, t_game *game)
{
	int		fd;
	char	*line;
	int		ret;

	fd = open(path, O_RDONLY);
	if (fd < 0)
		return (ft_putstr_fd("Error\nCannot open file\n", 2), 0);
	ret = 1;
	while (ret)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		if (is_map_line(line))
		{
			ret = handle_map_entry(game, fd, line);
			free(line);
			break ;
		}
		ret = parse_line(game, line);
		free(line);
	}
	get_next_line(-1);
	close(fd);
	return (ret && valid_map(game));
}
