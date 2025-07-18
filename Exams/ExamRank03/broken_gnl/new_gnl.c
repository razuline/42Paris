/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_gnl.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erazumov <erazumov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/11 17:02:02 by erazumov          #+#    #+#             */
/*   Updated: 2025/07/18 12:04:41 by erazumov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include "given_gnl.h"

static char	*ft_strchr(const char *s, int c)
{
	char	ch;

	ch = c;
	while (*s)
	{
		if (*s == ch)
			return ((char *)s);
		s++;
	}
	if (ch == '\0')
		return ((char *)s);
	return (NULL);
}

static size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	if (!s)
		return (0);
	while (s[i])
		i++;
	return (i);
}

static char	*ft_strjoin_free(char *s1, char *s2)
{
	size_t	i;
	size_t	j;
	char	*new_str;

	if (!s1)
	{
		s1 = malloc(1);
		if (!s1)
			return (NULL);
		s1[0] = '\0';
	}
	new_str = malloc(ft_strlen(s1) + ft_strlen(s2) + 1);
	if (!new_str)
	{
		free(s1);
		return (NULL);
	}
	i = 0;
	while (s1[i])
	{
		new_str[i] = s1[i];
		i++;
	}
	j = 0;
	while (s2[j])
	{
		new_str[i + j] = s2[j];
		j++;
	}
	new_str[i + j] = '\0';
	free(s1);
	return (new_str);
}

static char	*read_and_stash(int fd, char *stash)
{
	char	*buff;
	ssize_t	bytes_read;

	buff = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buff)
		return (NULL);
	bytes_read = 1;
	while (!ft_strchr(stash, '\n') && bytes_read > 0)
	{
		bytes_read = read(fd, buff, BUFFER_SIZE);
		if (bytes_read < 0)
		{
			free(buff);
			free(stash);
			return (NULL);
		}
		buff[bytes_read] = '\0';
		stash = ft_strjoin_free(stash, buff);
	}
	free(buff);
	return (stash);
}

static char	*extract_and_clean(char **stash)
{
	char	*line;
	char	*new_stash;
	char	*newline;
	size_t	line_len;
	size_t	i;

	newline = ft_strchr(*stash, '\n');
	if (!newline)
	{
		line = *stash;
		*stash = NULL;
		return (line);
	}
	line_len = (newline - *stash) + 1;
	line = malloc(sizeof(char) * (line_len + 1));
	if (!line)
		return (NULL);
	
	// --- CORRECTION 1 : Copier les caractères de la ligne ---
	i = 0;
	while (i < line_len)
	{
		line[i] = (*stash)[i];
		i++;
	}
	line[i] = '\0';

	new_stash = malloc(sizeof(char) * (ft_strlen(newline + 1) + 1));
	if (!new_stash)
	{
		free(line);
		return (NULL);
	}
	// --- CORRECTION 2 : Copier les caractères restants dans la nouvelle réserve ---
	i = 0;
	while ((newline + 1)[i])
	{
		new_stash[i] = (newline + 1)[i];
		i++;
	}
	new_stash[i] = '\0';

	// On libère l'ancienne réserve et on la met à jour
	free(*stash);
	*stash = new_stash;
	return (line);
}

char	*get_next_line(int fd)
{
	static char	*stash;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);

	// Étape 1: Lire depuis le fichier
	stash = read_and_stash(fd, stash);

	// On vérifie d'abord si stash est NULL
	if (!stash)
		return (NULL);
	// Ensuite, on vérifie s'il est vide
	if (*stash == '\0')
	{
		free(stash);
		stash = NULL;
		return (NULL);
	}
	// Étape 2: Extraire la ligne de la réserve
	line = extract_and_clean(&stash);

	return (line);
}
