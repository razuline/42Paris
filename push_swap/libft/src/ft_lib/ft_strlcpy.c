/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erazumov <erazumov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/09 18:15:33 by erazumov          #+#    #+#             */
/*   Updated: 2024/11/26 14:40:12 by erazumov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* Copy a string. Copy src to string dst of size siz. At most siz-1
characters will be copied. Always NULL terminates (unless siz == 0).
The strlcpy() function returns strlen(src). If retval >= siz,
truncation occurred. */

#include "libft.h"

size_t	ft_strlcpy(char *dest, const char *src, size_t size)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	while (src[j] != '\0')
		j++;
	if (size == 0)
		return (j);
	while (src[i] != '\0' && i < size - 1)
	{
		dest[i] = src[i];
		i++;
	}
	if (size > 0)
		dest[i] = '\0';
	return (j);
}
/*
void	ft_putchar(char c)
{
	write (1, &c, 1);
}

void	ft_putstr(char *str)
{
	int	i;

	i = 0;
	while (*(str + i))
		i++;
	write (1, str, i);
}

int	main(void)
{
	char src1[] = "Hello, World";
	char dest1[13];

	ft_strlcpy(dest1, src1, 13);
	ft_putstr(dest1);
	return (0);
}
*/