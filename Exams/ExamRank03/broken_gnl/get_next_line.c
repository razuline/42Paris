/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erazumov <erazumov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 13:08:51 by erazumov          #+#    #+#             */
/*   Updated: 2025/07/18 15:39:10 by erazumov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	ft_strlen(char *str)
{
	int	len;

	len = 0;
	if (!str)
		return (0);
	while (str[len])
		len++;
	return (len);
}

char	*ft_strchr(const char *s, int c)
{
	if (!s)
		return (NULL);
	while (*s != '\0')
	{
		if (*s == (char)c)
			return ((char *)s);
		s++;
	}
	if (*s == (char)c)
		return ((char *)s);
	return (NULL);
}

char	*ft_strdup(const char *s)
{
	int		i;
	int		len;
	char	*dup;

	if (!s)
		return (NULL);
	len = ft_strlen((char *)s);
	
	dup = malloc(len + 1);
	if (!dup)
		return (NULL);
	
	i = 0;
	while (i <= len)
	{
		dup[i] = s[i];
		i++;
	}
	return (dup);
}

char	*ft_strjoin_free(char *s1, char *s2)
{
	int		i;
	int		j;
	int		len1;
	int		len2;
	char	*joined;

	len1 = 0;
	len2 = 0;
	if (!s2)
		return (s1);
	if (s1)
		len1 = ft_strlen(s1);
	len2 = ft_strlen(s2);

	joined = malloc(len1 + len2 + 1);
	if (!joined)
	{
		free(s1);
		return (NULL);
	}

	i = 0;
	if (s1)
	{
		while (i < len1)
		{
			joined[i] = s1[i];
			i++;
		}
	}
	j = 0;
	while (j <= len2)
	{
		joined[i + j] = s2[j];
		j++;
	}
	free(s1);
	return (joined);
}

char	*get_next_line(int fd)
{
	int			bytes_read;
	char		*buff;
	char		*line = NULL;
	char		*newline;
	static char	*remainder = NULL;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);

	buff = malloc(BUFFER_SIZE + 1);
	if (!buff)
	{
		free(remainder);
		remainder = NULL;
		return (NULL);
	}

	if (remainder)
	{
		line = remainder;
		remainder = NULL;
	}
	else
	{
		line = ft_strdup("");
		if (!line)
		{
			free(buff);
			return (NULL);	
		}
	}

	while ((newline = ft_strchr(line, '\n')) == NULL)
	{
		bytes_read = read(fd, buff, BUFFER_SIZE);
		if (bytes_read == -1)
		{
			free(buff);
			free(line);
			free(remainder);
			remainder = NULL;
			return (NULL);
		}
		if (bytes_read == 0)
			break ;

		buff[bytes_read] = '\0';

		line = ft_strjoin_free(line, buff);
		if (!line)
		{
			free(buff);
			free(remainder);
			remainder = NULL;
			return (NULL);
		}
	}
	free (buff);

	if (newline)
	{
		remainder = ft_strdup(newline + 1);
		if (!remainder)
		{
			free(line);
			return (NULL);
		}
		*(newline + 1) = '\0';
	}
	if (!line || !*line)
	{
		free(line);
		return (NULL);
	}
	return (line);
}
