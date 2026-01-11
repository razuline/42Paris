/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erazumov <erazumov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/09 18:14:49 by erazumov          #+#    #+#             */
/*   Updated: 2024/11/26 14:34:14 by erazumov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* The  bzero()  function  erases  the  data  in the n bytes of the memory
starting at the location pointed to by s, by writing zeros
(bytes containing '\0') to that area. Returns nothing. */

#include "libft.h"

void	ft_bzero(void *dest, size_t len)
{
	ft_memset(dest, '\0', len);
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
	char dest1[] = "Hello, World";

	ft_bzero(dest1, 1);
	ft_putstr(dest1);
	return (0);
}
*/