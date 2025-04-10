/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printchar.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erazumov <erazumov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 14:14:43 by erazumov          #+#    #+#             */
/*   Updated: 2025/04/10 13:49:06 by erazumov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

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
