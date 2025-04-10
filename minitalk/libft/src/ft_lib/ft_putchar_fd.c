/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putchar_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erazumov <erazumov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 18:41:25 by erazumov          #+#    #+#             */
/*   Updated: 2024/11/26 15:15:51 by erazumov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* Outputs the character ’c’ to the given file descriptor. External functions:
write. Returns nothing. */

#include "libft.h"

void	ft_putchar_fd(char c, int fd)
{
	write(fd, &c, 1);
}
/*
int	main(void)
{
	char	my_letter;

	my_letter = 'c';
	ft_putchar_fd(my_letter, 2);
	ft_putchar_fd('\n', 2);
	return (0);
}
*/