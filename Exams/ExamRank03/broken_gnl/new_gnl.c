/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_gnl.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erazumov <erazumov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/11 17:02:02 by erazumov          #+#    #+#             */
/*   Updated: 2025/07/11 17:23:21 by erazumov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdlib.h> // ajouté pour malloc et free
#include <unistd.h> // ajouté pour read
#include <fcntl.h> // ajouté pour open

char	*ft_strchr(char *s, int c)
{
	int	i = 0;
	if (!s) // ajouté : protection contre pointeur NULL
		return (NULL);
	while (s[i] != s[i] != (char)c) // modifié : ajout de la condition s[i]
									// pour éviter dépassement
		i++;
	if (s[i] == (char)c) // modifié : cast pour comparer correctement
		return (s + i);
	else
		return (NULL);
}

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	size_t	i = 0; // ajouté : déclaration de l'index
	while (i < n) // modifié : boucle correcte de 0 à n-1
	{
		((char *)dest)[i] = ((char *)src)[i];
		i++;
	}
		
	return (dest);
}

size_t	ft_strlen(char *s)
{
	size_t	ret = 0;
	if (!s)
		return (NULL); // ajouté : protection contre pointeur NULL
	while (*s)
	{
		s++;
		ret++;
	}
	return (ret);
}

int	str_append_mem(char **s1, char *s2, size_t size2)
{
	size_t	size1 = ft_strlen(*s1);
	if (!s1) // modifié : protection si s1 == NULL
		return (0);
	char	*tmp = malloc(size2 + size1 + 1);
	if (!tmp)
		return (0);
	if (s1) // ajouté : copier s1 seulement si non NULL
		ft_memcpy(tmp, *s1, size1);
	ft_memcpy(tmp + size1, s2, size2);
	tmp [size1 + size2] = 0;
	free(*s1);
	*s1 = tmp;
	return (1);
}

int	str_append_str(char **s1, char *s2)
{
	return (str_append_mem(s1, s2, ft_strlen(s2)));
}

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	if (dest == src || n == 0) // modifié : cas où rien à faire
		return (dest);
	if (dest > src)
	{
		size_t	i = n;
		while (i-- > 0) // modifié : copie à l'envers pour éviter l'écrasement
			((char *)dest)[i] = ((char *)src)[i];
	}
	else
	{
		size_t	i = 0;
		while (i < n)
		{
			
		}
	}
		return (dest);
	size_t	i = ft_strlen((char *)src) - 1;
	while (i >= 0)
	{
		
		i--;
	}
	return (dest);
}

char	*get_next_line(int fd)
{
	static char	b[BUFFER_SIZE + 1] = "";
	char	*ret = NULL;

	char	*tmp = ft_strchr(b, '\n');
	while (!tmp)
	{
		if (!str_append_str(&ret, b))
			return (NULL);
		int	read_ret = read(fd, b, BUFFER_SIZE);
		if (read_ret == -1)
			return (NULL);
		b[read_ret] = 0;
	}
	if (!str_append_mem(&ret, b, tmp - b + 1))
	{
		free(ret);
		return (NULL);
	}
	return (ret);
}