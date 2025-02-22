/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isprint.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erazumov <erazumov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/09 18:14:10 by erazumov          #+#    #+#             */
/*   Updated: 2024/11/26 14:24:46 by erazumov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* Checks for any printable character including space. */

#include "libft.h"

int	ft_isprint(int c)
{
	if (c >= 32 && c < 127)
		return (1);
	return (0);
}
/*
int	main(void)
{
	int	c;

	c = ' ';
	if (ft_isprint(c) == 1)
		write (1, "Printable", 10);
	else
		write (1, "Another character", 17);
	return (0);
}
*/