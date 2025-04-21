/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erazumov <erazumov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 16:36:23 by erazumov          #+#    #+#             */
/*   Updated: 2025/04/21 18:21:11 by erazumov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* Write a function that returns a line read from a
file descriptor.
fd: The file descriptor to read from.
Return value:
Read line: correct behavior; NULL: there is nothing else to read, or an error
occurred. */

#include "libft.h"

static char	*join_and_upd(char *remainder, char *buff)
{
	char	*tmp_join;

	tmp_join = ft_str_join(remainder, buff);
	if (remainder)
	{
		free(remainder);
		remainder = NULL;
	}
	return (tmp_join);
}

char	*ft_read(int fd, char *remainder)
{
	char	*buff;
	int		bytes_read;

	if (!(buff = malloc(sizeof(char) * (BUFFER_SIZE + 1))))
		return (ft_if_error(remainder));
	bytes_read = 1;
	while (bytes_read > 0)
	{
		if (remainder && ft_strchr(remainder, '\n'))
			break ;
		bytes_read = read(fd, buff, BUFFER_SIZE);
		if (bytes_read <= 0)
			break ;
		buff[bytes_read] = '\0';
		remainder = join_and_upd(remainder, buff);
		if (!remainder)
		{
			bytes_read = -1;
			break ;
		}
	}
	free(buff);
	if (bytes_read == -1)
		return (ft_if_error(remainder));
	return (remainder);
}

char	*ft_get_line(char *remainder)
{
	int		i;
	char	*line;

	i = 0;
	if (!remainder[i])
		return (NULL);
	while (remainder[i] && remainder[i] != '\n')
		i++;
	line = (char *)malloc(sizeof(char) * (i + 2));
	if (!line)
		return (NULL);
	i = 0;
	while (remainder[i] && remainder[i] != '\n')
	{
		line[i] = remainder[i];
		i++;
	}
	if (remainder[i] == '\n')
	{
		line[i] = remainder[i];
		i++;
	}
	line[i] = '\0';
	return (line);
}

char	*ft_cut_line(char *remainder)
{
	int		i;
	int		j;
	char	*new_remainder;

	i = 0;
	while (remainder[i] && remainder[i] != '\n')
		i++;
	if (!remainder[i])
		return (ft_if_error(remainder));
	new_remainder = (char *)malloc(sizeof(char) * (ft_strlen(remainder)
				- i + 1));
	if (!new_remainder)
		return (NULL);
	i++;
	j = 0;
	while (remainder[i])
		new_remainder[j++] = remainder[i++];
	new_remainder[j] = '\0';
	ft_if_error(remainder);
	return (new_remainder);
}

char	*get_next_line(int fd)
{
	char		*line;
	static char	*remainder;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (0);
	remainder = ft_read(fd, remainder);
	if (!remainder)
		return (NULL);
	line = ft_get_line(remainder);
	remainder = ft_cut_line(remainder);
	return (line);
}
/*
#include <stdio.h>

int	main(int argc, char const *argv[])
{
	int		fd;
	int		count;
	char	*line;

	if (argc != 2)
		return (-1);
	fd = open(argv[1], O_RDONLY);
	count = 19;
	line = get_next_line(fd);
	while (line != NULL)
	{
		printf("%s", line);
		free(line);
		line = get_next_line(fd);
		count--;
	}
	free(line);
	close(fd);
	return (0);
}
*/
