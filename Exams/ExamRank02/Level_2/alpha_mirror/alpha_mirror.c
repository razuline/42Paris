/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   alpha_mirror.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erazumov <erazumov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 21:19:06 by erazumov          #+#    #+#             */
/*   Updated: 2025/05/13 21:27:14 by erazumov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

void	alpha_mirror(char *str)
{
	while (*str)
	{
		if (*str >= 'A' && *str <= 'Z')
			write(1, &(char){'Z' - (*str - 'A')}, 1);
		else if (*str >= 'a' && *str <= 'z')
			write(1, &(char){'z' - (*str - 'a')}, 1);
		else
			write(1, str, 1);
		str++;
	}
}

int	main(int ac, char **av)
{
	if (ac == 2)
		alpha_mirror(av[1]);
	write(1, "\n", 1);
	return (0);
}
