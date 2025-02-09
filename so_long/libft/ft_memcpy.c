/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erazumov <erazumov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/09 18:15:02 by erazumov          #+#    #+#             */
/*   Updated: 2024/11/26 14:36:10 by erazumov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* The  memcpy()  function  copies  n bytes from memory area src to memory
area dest. The memory areas must not overlap. Use memmove(3) if the memory
areas do overlap.
The memcpy() function returns a pointer to dest. */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	char	*n_dest;
	char	*n_src;
	size_t	i;

	n_dest = (char *)dest;
	n_src = (char *)src;
	i = 0;
	if (!n_dest && !n_src)
		return (NULL);
	if (n_dest != n_src)
	{
		while (i < n)
		{
			n_dest[i] = n_src[i];
			i++;
		}
	}
	return (dest);
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
	char dest1[30];

	ft_memcpy(dest1, src1, ft_strlen(src1) + 1);
	ft_putstr(dest1);
	return (0);
}
*/