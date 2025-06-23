/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erazumov <erazumov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/09 18:15:43 by erazumov          #+#    #+#             */
/*   Updated: 2024/11/26 15:40:19 by erazumov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* Concatenate two strings. Appends src to string dst of size siz (unlike
strncat(), siz is the full size of dst, not space left). At most siz-1
characters will be copied. Always NULL terminates
(unless siz <= strlen(dst)).
The strlcat() function returns strlen(src) + MIN(siz, strlen(initial dst)). 
If retval >= siz, truncation occurred. */

#include "libft.h"

size_t	ft_strlcat(char *dest, const char *src, size_t size)
{
	size_t	dest_len;
	size_t	src_len;
	size_t	total_len;
	size_t	i;

	dest_len = ft_strlen(dest);
	src_len = ft_strlen(src);
	total_len = dest_len + src_len;
	if (size <= 0)
		return (src_len);
	if (size <= dest_len)
		return (src_len + size);
	i = 0;
	while (dest_len + i < size - 1 && src[i] != '\0')
	{
		dest[dest_len + i] = src[i];
		i++;
	}
	dest[dest_len + i] = '\0';
	return (total_len);
}
/*
void	ft_putchar(char c)
{
	write (1, &c, 1);
}

void	ft_putnbr(int nb)
{
	if (nb == -2147483648)
	{
		ft_putchar('-');
		ft_putchar('2');
		nb = 147483648;
	}
	if (nb < 0)
	{
		ft_putchar('-');
		nb *= -1;
	}
	if (nb > 9)
	{
		ft_putnbr(nb / 10);
		ft_putnbr(nb % 10);
	}
	else
	{
		ft_putchar(nb + '0');
	}
}

int	main(void)
{
	char	dest1[] = "Hello, ";
	char	src1[] = "World!";

	ft_putnbr(ft_strlcat(dest1, src1, 7));
	write (1, "\n", 1);
	return (0);
}
*/