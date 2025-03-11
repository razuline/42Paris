/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printnbr.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: razuline <razuline@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 14:46:37 by erazumov          #+#    #+#             */
/*   Updated: 2024/12/02 16:49:49 by razuline         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_printnbr(int n)
{
	int		len;
	char	*num;

	len = 0;
	num = ft_itoa(n);
	len = ft_printstr(num);
	free (num);
	return (len);
}
/*
#include <stdio.h>

int	main(void)
{
	int nb;
	int	len;

	nb = 10;
	len = ft_printnbr(nb);
	printf("%d\n", len);
	return (0);
}
*/