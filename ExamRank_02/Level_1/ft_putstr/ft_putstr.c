/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erazumov <erazumov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/10 17:45:54 by erazumov          #+#    #+#             */
/*   Updated: 2025/05/11 10:53:03 by erazumov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

void	ft_putstr(char *str)
{
	while (*str)
		write(1, &*str++, 1);
}
/*
int	main(void)
{
	ft_putstr("Hello, world!\n");
	ft_putstr("");
	ft_putstr("A\n");
	ft_putstr("\tTab\nNew line\n");
	ft_putstr("This is a very long string to test if the function can handle it properly without any issues.\n");
	return (0);
}
*/