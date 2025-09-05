/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erazumov <erazumov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/09 18:17:49 by erazumov          #+#    #+#             */
/*   Updated: 2025/08/12 16:13:34 by erazumov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* The  strchr() function returns a pointer to the first occurrence of the
character c in the string s.
The strchr() function returns a pointer to the matched character or NULL
if the character is not found. The terminating null byte is considered part
of the string, so that if c is specified as '\0', this function
returns a pointer to the terminator. */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	char	ch;

	if (!s)
		return (NULL);
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
	if (ft_strchr(str, ch) != 0)
		ft_putstr("Character is found.\n");
	else
		ft_putstr("Character is not found.\n");
	return (0);
}
*/