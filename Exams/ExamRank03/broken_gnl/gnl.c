/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gnl.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erazumov <erazumov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/20 20:28:13 by erazumov          #+#    #+#             */
/*   Updated: 2025/07/20 20:50:40 by erazumov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gnl.h"

static char	*join_and_free(char *line, char *chunk, int chunk_len)
{
	int		i;
	int		j;
	int		line_len;
	char	*new_line;

	if (!line)
	{
		line = malloc(1);
		line[0] = '\0';
	}
	line_len = 0;
	while (line[line_len])
		line_len++;
	new_line = malloc(line_len + chunk_len + 1);
	if (!new_line)
	{
		free(line);
		return (NULL);
	}
	i = -1;
	while (++i < line_len)
		new_line[i] = line[i];
	j = -1;
	while (++j < chunk_len)
		new_line[i + j] = chunk[j];
	new_line[i + j] = '\0';
	free(line);
	return (new_line);
}

char	*get_next_line(int fd)
{
	static char	buf[BUFFER_SIZE];
	static int	bytes_buf;
	static int	pos;
	char		*line;
	int			found;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (0);
	line = NULL;
	found = 0;
	while (!found)
	{
		if (pos >= bytes_buf)
		{
			bytes_buf = read(fd, buf, BUFFER_SIZE);
			pos = 0;
			if (bytes_buf <= 0)
				break ;
		}
		int	chunk_start = pos;
		while (pos < bytes_buf && buf[pos] != '\n')
			pos++;
		if (pos < bytes_buf && buf[pos] == '\n')
		{
			pos++;
			found = 1;
		}
		line = join_and_free(line, buf + chunk_start, pos - chunk_start);
		if (!line)
			return (NULL);
	}
	if (bytes_buf < 0)
	{
		free(line);
		return (NULL);
	}
	return (line);
}
