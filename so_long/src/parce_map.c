/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parce_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erazumov <erazumov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/22 11:23:13 by erazumov          #+#    #+#             */
/*   Updated: 2025/03/22 12:45:47 by erazumov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "so_long.h"

int	get_map_height(char *map_file)
{
	int		fd;
	int		height;
	char	*line;

	fd = open(map_file, O_RDONLY);
	if (fd < 0)
		return (0);
	height = 0;
	while ((line = get_next_line(fd)))
	{
		height++;
		free(line);
	}
	close(fd);
	return (height);
}

int	read_map(char *map_file, t_map *map)
{
	int	i;
	int	fd;

	map->height = get_map_height(map_file);
	if (map->height == 0)
		return (0);
	map->grid = malloc(sizeof(char *) * (map->height + 1));
	if (!map->grid)
		return (NULL);
	fd = open(map_file, O_RDONLY);
	if (fd < 0)
		return (0);
	i = 0;
	while (i < map->height)
	{
		map->grid[i] = get_next_line(fd);
		if (!map->grid[i])
			return (0);
		i++;
	}
	map->grid[i] = NULL;
	close(fd);
	return (1);
}

int	check_walls(t_map *map)
{
	int	i;

	i = 0;
	while (i < map->width)
	{
		if (map->grid[0][i] != '1' || map->grid[map->height - 1][i] != '1')
			return (0);
		i++;
	}
	i = 0;
	while (i < map->height)
	{
		if (map->grid[i][0] != '1' || map->grid[i][map->width - 1] != '1')
			return (0);
		i++;
	}
	return (1);
}

static void	count_elements(t_map *map, int x, int y, int *player_count)
{
	if (map->grid[y][x] == 'P')
	{
		map->player_x = x;
		map->player_y = y;
		(*player_count)++;
	}
	else if (map->grid[y][x] == 'C')
		map->object++;
	else if (map->grid[y][x] == 'E')
	{
		map->exit_x = x;
		map->exit_y = y;
	}
}

static bool	is_valid_element(char c)
{
	return (c == '0' || c == '1' || c == 'P' || c == 'C' || c == 'E');
}

int	check_elements(t_map *map)
{
	int	x;
	int	y;
	int	player_count;

	player_count = 0;
	map->object = 0;
	y = 0;
	while (y < map->height)
	{
		x = 0;
		while (x < map->width)
		{
			if (!is_valid_element(map->grid[y][x]))
				return (false);
			count_elements(map, x, y, &player_count);
			x++;
		}
		y++;
	}
	return (player_count == 1 && map->object > 0 && map->exit_x >= 0);
}

int	parce_map(t_map *map, char *map_file)
{
	if (!read_map(map_file, map))
	{
		ft_printf("Error: failed to read map.\n");
		return (0);
	}
	map->width = ft_strlen(map->grid[0]) - 1;
	if (!check_walls(map) || !check_elements(map))
	{
		ft_printf("Error: invalid map.\n");
		return (0);
	}
	return (1);
}
