/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erazumov <erazumov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 17:39:42 by erazumov          #+#    #+#             */
/*   Updated: 2025/02/09 16:02:15 by erazumov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "so_long.h"

char	**read_map(char *file)
{
	int		fd;
	int		bytes;
	char	*buff;
	char	**map;

	fd = open(file, O_RDONLY);
	if (fd < 0)
		return (NULL);
	buff = malloc(10000); /* The 10 KB limit */
	bytes = read(fd, buff, 9999);
	buff[bytes] = '\0';
	close(fd);

	map = ft_split(buff, '\n');
	free(buff);
	return (map);
}

# include <stdio.h>

int	main(void)
{
	int		i;
	char	**map;

	map = read_map("map.ber");

	if (!map)
	{
		printf("Error: could not read a map!\n");
		return (1);
	}
	i = 0;
	while (map[i])
	{
		printf("%s\n", map[i]);
		i++;
	}
	return (0);
}
