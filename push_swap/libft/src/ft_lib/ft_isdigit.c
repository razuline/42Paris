/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isdigit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erazumov <erazumov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/09 18:12:49 by erazumov          #+#    #+#             */
/*   Updated: 2024/11/26 14:22:50 by erazumov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* Checks for a digit (0 through 9). */

#include "libft.h"

int	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}
/*
int	main(void)
{
	int	c;

	c = '1';
	if (ft_isdigit(c) == 1)
		write(1, "Digit", 5);
	else
		write(1, "Another character", 17);
	return (0);
}
*/