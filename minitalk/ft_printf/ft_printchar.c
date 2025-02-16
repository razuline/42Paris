/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printchar.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: razuline <razuline@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 14:14:43 by erazumov          #+#    #+#             */
/*   Updated: 2024/12/02 16:49:34 by razuline         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_printchar(char c)
{
	write(1, &c, 1);
	return (1);
}
/*
int	main(void)
{
	char	c;

	c = 'G';
	ft_printchar(c);
	ft_printchar('\n');
	return (0);
}
*/