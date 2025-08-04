/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filter.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erazumov <erazumov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 12:01:22 by erazumov          #+#    #+#             */
/*   Updated: 2025/07/29 13:31:39 by erazumov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

/*
** Vérifie si le début de 'buff' correspond à la chaîne 's'.
** L'appelant doit s'assurer que 'buff' est assez long.
*/
int	is_match(const char *buff, const char *s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (buff[i] != s[i])
			return (0);
		i++;
	}
	return (1);
}

/*
** Lit l'intégralité de l'entrée standard et la retourne.
*/
char	*read_stdin(void)
{
	int		i;
	char	*buff;
	char	chunk[1024];
	size_t	total_size = 0;
	ssize_t	bytes_read;

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
	int		input_len;
	char	*s;
	char	*input;

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

	if (s_len > 0)
	{
		i = 0;
		input_len = strlen(input);
		while (i < input_len)
		{
			if ((i <= input_len - s_len) && is_match(input + i, s))
			{
				j = 0;
				while (j < s_len)
				{
					input[i + j] = '*';
					j++;
				}
				i += s_len;
			}
			else
				i++;
		}
	}
	printf("%s", input);
	free(input);

	return (0);
}
