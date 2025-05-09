/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erazumov <erazumov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/09 18:18:01 by erazumov          #+#    #+#             */
/*   Updated: 2024/11/26 14:47:32 by erazumov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* The strrchr() function returns a pointer to the last occurrence of the
character c in the string s.
The strrchr() function returns a pointer to the matched character or NULL
if the character is not found. The terminating null byte is considered part
of the string, so that if c is specified as '\0', this function
returns a pointer to the terminator. */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int	i;

	i = ft_strlen(s);
	while (i >= 0)
	{
		if (s[i] == (char)c)
			return ((char *) &s[i]);
		i--;
	}
	if (!(char)c)
		return ((char *) &s[i]);
	return (0);
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
	if (ft_strrchr(str, ch) != 0)
		ft_putstr("Character is found.\n");
	else
		ft_putstr("Character is not found.\n");
	return (0);
}
*/