/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erazumov <erazumov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/18 11:49:27 by erazumov          #+#    #+#             */
/*   Updated: 2025/07/20 20:46:25 by erazumov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gnl.h"
#include <fcntl.h>
#include <stdio.h>

int	main(int ac, char **av)
{
	int		fd;
	char	*line;

	if (ac != 2)
	{
		printf("Usage: %s <filename>\n", av[0]);
		return (1);
	}
	fd = open(av[1], O_RDONLY);
	if (fd < 0)
	{
		perror("Error opening file");
		return (1);
	}
	// On appelle get_next_line en boucle jusqu'à la fin du fichier (elle renvoie NULL)
	while ((line = get_next_line(fd)) != NULL)
	{
		printf("%s", line);
		// Très important : on libère la mémoire après chaque ligne
		free(line);
	}
	close(fd);
	return (0);
}
