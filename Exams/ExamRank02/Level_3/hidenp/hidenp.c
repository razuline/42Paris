/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hidenp.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erazumov <erazumov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 19:52:46 by erazumov          #+#    #+#             */
/*   Updated: 2025/05/09 20:02:11 by erazumov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

int	is_hidden(char *s1, char *s2)
{
	if (*s1 == '\0')
		return (1);
	while (*s2 != '\0')
	{
		if (*s1 == *s2)
		{
			s1++;
			if (*s1 == '\0')
				return (1);
		}
		s2++;
	}
	return (0);
}

int	main(int ac, char **av)
{
	if (ac != 3)
	{
		write(1, "\n", 1);
		return (0);
	}
	if (is_hidden(av[1], av[2]))
		write(1, "1\n", 2);
	else
		write(1, "0\n", 2);
	return (0);
}
