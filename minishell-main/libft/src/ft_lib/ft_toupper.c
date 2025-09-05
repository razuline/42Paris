/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_toupper.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erazumov <erazumov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/09 18:16:25 by erazumov          #+#    #+#             */
/*   Updated: 2024/11/26 14:28:02 by erazumov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* These functions convert lowercase letters to uppercase, and vice versa.
If c is a lowercase letter, toupper() returns its uppercase equivalent,
if an uppercase representation exists in the  current  locale.   Other‐
wise, it  returns c.
The value returned is that of the converted letter, or c if the conversion
was not possible. */

#include "libft.h"

int	ft_toupper(int c)
{
	if (c >= 'a' && c <= 'z')
		c -= 32;
	return (c);
}
/*
#include <stdio.h>

int	main(void)
{
	int	c = 'a';
	int	result = ft_toupper(c);
	printf("%d\n", c);
	printf("%d\n", result);
	return (0);
}
*/