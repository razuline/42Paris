/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isascii.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erazumov <erazumov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/09 18:13:21 by erazumov          #+#    #+#             */
/*   Updated: 2024/11/26 14:24:16 by erazumov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* Checks whether c is a 7-bit unsigned char value that fits into
the ASCII character set. */

#include "libft.h"

int	ft_isascii(int c)
{
	if (c >= 0 && c <= 127)
		return (1);
	return (0);
}
/*
int	main(void)
{
	int	c;

	c = 'G';
	if (ft_isascii(c) == 1)
		write (1, "ASCII character", 15);
	else
		write (1, "Another character", 17);
	return (0);
}
*/