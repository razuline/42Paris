/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalnum.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erazumov <erazumov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/09 18:13:06 by erazumov          #+#    #+#             */
/*   Updated: 2024/11/26 14:23:34 by erazumov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* Checks for an alphanumeric character;
it is equivalent to (isalpha(c) || isdigit(c)). */

#include "libft.h"

int	ft_isalnum(int c)
{
	if ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z')
		|| (c >= '0' && c <= '9'))
		return (1);
	return (0);
}
/*
int	main(void)
{
	int	c;

	c = '5';
	if (ft_isalnum(c) == 1)
		write (1, "Alpha or digit", 14);
	else
		write (1, "Another character", 17);
	return (0);
}
*/