/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_gnl.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erazumov <erazumov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/11 17:02:02 by erazumov          #+#    #+#             */
/*   Updated: 2025/07/11 17:28:37 by erazumov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUFFER_SIZE
# define BUFFER_SIZE 3
#endif

#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

//cc broken_gnl.c -Wall -Wextra -Werror -D BUFFER_SIZE=3 -o gnl

int	ft_strlen(char *c)
{
	int	i;

	i = 0;
	if (c == NULL)
		return (0);
	while (c[i])
	{
		i++;
	}
	return (i);
}

char	*ft_strchr(char *s, int c)
{
	int	i;

	i = 0;
	while (s[i] && s[i] != c)
	{
		i++;
	}
	if (s[i] == c)
		return (&s[i]);
	return (NULL);
}

char	*ft_memmove(char *dest, char *src, int n)
{
	int	i;

	if (dest == NULL && src == NULL)
		return (NULL);
	if (src > dest)
	{
		i = 0;
		while (i < n)
		{
			dest[i] = src[i];
			i++;
		}
	}
	else
	{
		i = n - 1;
		while (i >= 0)
		{
			dest[i] = src[i];
			i--;
		}
	}
	return (dest);
}

char	*ft_join(char *s1, char *s2, int n)
{
	int		size1;
	char	*retj;

	size1 = ft_strlen(s1);
	retj = malloc(sizeof(char) * (size1 + n + 1));
	if (retj == NULL)
	{
		free(s1);
		return (NULL);
	}
	ft_memmove(retj, s1, size1);
	ft_memmove(retj + size1, s2, n);
	retj[size1 + n] = '\0';
	free(s1);
	s1 = NULL;
	return (retj);
}

char	*b_gnl(fd)
{
	static char	buf[BUFFER_SIZE + 1];
	char		*tmp;
	char		*rest;
	int			nb_read;
	int			deb;
	int			j;

	tmp = NULL;
	rest = NULL;
	nb_read = 0;
	//	printf("buffer_size  = %d\n", BUFFER_SIZE);
	while (rest == NULL)
	{
		if (buf[0] == '\0')
		{
			nb_read = read(fd, buf, BUFFER_SIZE);
			if (nb_read == 0)
			{
				free(tmp);
				return (NULL);
			}
		}
		rest = ft_strchr(buf, '\n');
		if (rest)
		{
			deb = 0;
			deb = rest - buf;
			tmp = ft_join(tmp, buf, deb + 1);
			j = 0;
			while (buf[j + deb + 1])
			{
				buf[j] = buf[j + deb + 1];
				j++;
			}
			buf[j] = '\0';
			return (tmp);
		}
		else
		{
			tmp = ft_join(tmp, buf, ft_strlen(buf));
			buf[0] = '\0';
		}
	}
	return (tmp);
}

int	main(void)
{
	int fd = 0;

	fd = open("text1.txt", O_RDONLY);
	if (fd < 0)
		perror("open");

	printf("line = %s", b_gnl(fd));
	printf("line = %s", b_gnl(fd));
	printf("line = %s", b_gnl(fd));
	printf("line = %s", b_gnl(fd));
	printf("line = %s", b_gnl(fd));
	printf("line = %s", b_gnl(fd));
	printf("line = %s", b_gnl(fd));

	return (0);
}