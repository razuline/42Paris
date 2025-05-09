/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erazumov <erazumov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 18:42:12 by erazumov          #+#    #+#             */
/*   Updated: 2024/11/26 15:16:31 by erazumov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* Outputs the string ’s’ to the given file descriptor. External functions:
write. Returns nothing. */

#include "libft.h"

void	ft_putstr_fd(char *s, int fd)
{
	while (*s)
		write(fd, s++, 1);
}
/*
int	main(void)
{
	char	*s;

	s = "Hello!";
	ft_putstr_fd(s, 2);
	return (0);
}
*/