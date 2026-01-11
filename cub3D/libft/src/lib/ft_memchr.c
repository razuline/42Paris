/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erazumov <erazumov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/09 18:18:39 by erazumov          #+#    #+#             */
/*   Updated: 2024/11/26 14:52:21 by erazumov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* The memchr() function scans the initial n bytes of the memory area
pointed to by s for the first instance of c. Both c and the bytes of
the memory area pointed to by s are interpreted as unsigned char. 
The  memchr() function returns a pointer to the matching byte or NULL
if the character does not occur in the given memory area. */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t len)
{
	char	*n_s;
	char	n_c;
	size_t	i;

	n_s = (char *)s;
	n_c = (char)c;
	i = 0;
	while (i < len)
	{
		if (n_c == n_s[i])
			return (n_s + i);
		i++;
	}
	return (NULL);
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

int	main(void)
{
	char	*str;
	char	ch;

	str = "Hello";
	ch = 'E';

	ft_putstr(str);
	ft_putchar('\n');
	if (ft_memchr(str, ch, 2) != 0)
		ft_putstr("Character is found.\n");
	else
		ft_putstr("Character is not found.\n");
	return (0);
}
*/