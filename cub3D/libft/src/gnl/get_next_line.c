/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mayoucha <mayoucha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 16:36:23 by erazumov          #+#    #+#             */
/*   Updated: 2026/01/11 18:29:25 by mayoucha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* Write a function that returns a line read from a
file descriptor.
fd: The file descriptor to read from.
Return value:
Read line: correct behavior; NULL: there is nothing else to read, or an error
occurred. */

#include "libft.h"

static char	*join_and_upd(char *remainder, char *buf)
{
	char	*new_str;

	new_str = ft_str_join(remainder, buf);
	free(remainder);
	return (new_str);
}

char	*ft_read(int fd, char *res)
{
	char	*buf;
	int		rd;

	buf = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buf)
		return (ft_if_error(res));
	rd = 1;
	while (rd > 0 && (!res || !ft_strchr(res, '\n')))
	{
		rd = read(fd, buf, BUFFER_SIZE);
		if (rd == -1)
			break ;
		buf[rd] = '\0';
		res = join_and_upd(res, buf);
	}
	free(buf);
	if (rd == -1)
		return (ft_if_error(res));
	return (res);
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

char	*ft_cut_line(char *rem)
{
	int		i;
	int		j;
	char	*new_rem;

	i = 0;
	while (rem[i] && rem[i] != '\n')
		i++;
	if (!rem[i])
	{
		free(rem);
		return (NULL);
	}
	new_rem = (char *)malloc(sizeof(char) * (ft_strlen(rem) - i + 1));
	if (!new_rem)
	{
		free(rem);
		return (NULL);
	}
	i++;
	j = 0;
	while (rem[i])
		new_rem[j++] = rem[i++];
	new_rem[j] = '\0';
	free(rem);
	return (new_rem);
}

char	*get_next_line(int fd)
{
	char		*line;
	static char	*remainder;

	if (fd < 0)
	{
		if (remainder)
		{
			free(remainder);
			remainder = NULL;
		}
		return (NULL);
	}
	if (BUFFER_SIZE <= 0)
		return (NULL);
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
