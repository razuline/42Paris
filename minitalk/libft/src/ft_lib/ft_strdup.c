/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erazumov <erazumov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/09 18:20:23 by erazumov          #+#    #+#             */
/*   Updated: 2024/11/26 15:44:58 by erazumov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* The strdup() function returns a pointer to a new string which is a duplicate
of the string s. Memory for the new string is obtained with malloc(3),
and can be freed with free(3).
On success, the strdup() function returns a pointer to the duplicated string.
It returns NULL if insufficient memory was available, with errno set to indicate
the cause of the error. */

#include "libft.h"

char	*ft_strdup(const char *src)
{
	int		i;
	char	*dest;

	i = 0;
	dest = malloc(sizeof(char) * ft_strlen(src) + 1);
	if (dest == NULL)
		return (NULL);
	while (src[i])
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = 0;
	return (dest);
}
/*
void	ft_putchar(char c)
{
	write (1, &c, 1);
}

void	ft_putstr(char *str)
{
	while (*str != '\0')
	{
		ft_putchar(*str);
		str++;
	}
}

int	main(int argc, char **argv)
{
	char	*dup;

	if (argc > 1)
	{
		dup = ft_strdup(argv[1]);
		ft_putstr(dup);
		ft_putchar('\n');
		free (dup);
	}
	return (0);
}
*/