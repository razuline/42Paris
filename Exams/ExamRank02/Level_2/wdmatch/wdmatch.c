/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wdmatch.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erazumov <erazumov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 21:21:14 by erazumov          #+#    #+#             */
/*   Updated: 2025/05/13 22:06:27 by erazumov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

void	ft_putstr(char *str)
{
	while (*str)
		write(1, str++, 1);
}

int	wdmatch(char *s1, char *s2)
{
	while (*s2)
	{
		if (*s1 == *s2)
			s1++;
		if (*s1 == '\0')
			return (1);
		s2++;
	}
	return (0);
}

int	main(int ac, char **av)
{
	if (ac == 3 && wdmatch(av[1], av[2]))
		ft_putstr(av[1]);
	write(1, "\n", 1);
	return (0);
}
