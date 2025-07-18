/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filter.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erazumov <erazumov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 12:01:22 by erazumov          #+#    #+#             */
/*   Updated: 2025/07/18 10:43:04 by erazumov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int	is_match(const char *buffer, const char *s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (buffer[i] != s[i])
			return (0);
		i++;
	}
	return (1);
}

char	*read_stdin(void)
{
	int		i;
	char	*buff;
	char	chunk[1024];
	size_t	total_size;
	ssize_t	bytes_read;

	total_size = 0;
	buff = malloc(1);
	if (!buff)
		return (NULL);
	buff[0] = '\0';
	while ((bytes_read = read(STDIN_FILENO, chunk, 1024)) > 0)
	{
		
		buff = realloc(buff, total_size + bytes_read + 1);
		if (!buff)
			return (NULL);
		i = 0;
		while (i < bytes_read)
		{
			buff[total_size + i] = chunk[i];
			i++;
		}
		total_size += bytes_read;
		buff[total_size] = '\0';
	}
	if (bytes_read < 0)
	{
		free(buff);
		return (NULL);
	}
	return (buff);
}

int	main(int ac, char **av)
{
	int		i;
	int		j;
	int		s_len;
	char	*s;
	char	*input;
	char	*result;

	if (ac != 2)
		return (1);
	s = av[1];
	s_len = strlen(s);
	input = read_stdin();
	if (!input)
	{
		perror("Error");
		return (1);
	}
	result = malloc(strlen(input) + 1);
	if (!result)
	{
		free(input);
		perror("Error");
		return (1);
	}
	i = 0;
	j = 0;
	if (s_len > 0)
	{
		while (input[i])
		{
			if (is_match(input + i, s))
				i += s_len;
			else
			{
				result[j] = input[i];
				i++;
				j++;
			}
		}
	}
	result[j] = '\0';
	printf("%s", result);
	free(input);
	free(result);
	return (0);
}
