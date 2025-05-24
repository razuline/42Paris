/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erazumov <erazumov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 13:08:51 by erazumov          #+#    #+#             */
/*   Updated: 2025/05/24 13:35:12 by erazumov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	ft_strlen(char *str)
{
	int	len;

	len = 0;
	while (str[len])
		len++;
	return (len);
}

char	*ft_strchr(const char *s, int c)
{
	while (*s)
	{
		if (*s == (char)c)
			return ((char *)s);
		s++;
	}
	return (NULL);
}

char	*ft_strdup(const char *s)
{
	int		i;
	int		len;
	char	*dup;

	len = 0;
	while (s[len])
		len++;
	
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
	int		len1;
	int		len2;
	char	*joined;

	if (!s2)
		return (s1);

	len1 = ft_strlen(s1);
	len2 = ft_strlen(s2);
	joined = malloc(len1 + len2 + 1);
	if (!joined)
	{
		free(s1);
		return (NULL);
	}

	i = 0;
	while (i < len1)
	{
		joined[i] = s1[i];
		i++;
	}
	i = 0;
	while (i <= len2)
	{
		joined[len1 + i] = s2[i];
		i++;
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
		return (NULL);

	if (remainder)
	{
		line = remainder;
		remainder = NULL;
	}

	while ((newline = ft_strchr(line, '\n')) == NULL)
	{
		bytes_read = read(fd, buff, BUFFER_SIZE);
		if (bytes_read <= 0)
			break ;
		buff[bytes_read] = '\0';

		line = ft_strjoin_free(line, buff);
		if (!line)
			break ;
	}
	free (buff);

	if (bytes_read == -1)
	{
		free(line);
		return (NULL);
	}
	if (newline)
	{
		remainder = ft_strdup(newline + 1);
		*(newline + 1) = '\0';
	}
	if (!line || !*line)
	{
		free(line);
		return (NULL);
	}
	return (line);
}


#include <fcntl.h>
#include <stdio.h>

#ifndef BUFFER_SIZE
# define BUFFER_SIZE 32
#endif

#define RED "\033[31m"
#define GREEN "\033[32m"
#define YELLOW "\033[33m"
#define RESET "\033[0m"

static void	safe_test(const char *filename)
{
	printf(YELLOW "\n[%s]\n" RESET, filename);
	
	int		fd = open(filename, O_RDONLY);
	if (fd == -1)
	{
		printf(RED "  ✗ Open failed\n" RESET);
		return ;
	}

	char	*line;
	int		count = 1;
	while ((line = get_next_line(fd)))
	{
		printf(GREEN "  %2d: %s" RESET, count++, line);
		free(line);
	}
	close(fd);
}

int	main(void)
{
	// Text files only (no binary)
	system("echo -e 'Line 1\\nLine 2' > normal.txt");
	system("echo -n 'No newline' > no_nl.txt");
	system("echo -e '\\n\\n' > multi_nl.txt");
	system("echo -n 'A very very very very very long line' > long.txt");

	safe_test("normal.txt");
	safe_test("no_nl.txt");
	safe_test("multi_nl.txt");
	safe_test("long.txt");

	// Edge cases
	printf(YELLOW "\n[Edge Cases]\n" RESET);
	printf("Invalid FD: ");
	char	*res = get_next_line(-1);
	!res ? printf(GREEN "✓ NULL\n" RESET) : printf(RED "✗ Got: %s\n" RESET, res);
	free(res);

	printf("Empty file: ");
	system("touch empty.txt");
	int	fd = open("empty.txt", O_RDONLY);
	res = get_next_line(fd);
	!res ? printf(GREEN "✓ NULL\n" RESET) : printf(RED "✗ Got: %s\n" RESET, res);
	free(res);
	close(fd);

	// Cleanup
	system("rm -f normal.txt no_nl.txt multi_nl.txt long.txt empty.txt");
	return (0);
}
