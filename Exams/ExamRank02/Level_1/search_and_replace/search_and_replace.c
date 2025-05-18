/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   search_and_replace.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erazumov <erazumov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/10 17:39:27 by erazumov          #+#    #+#             */
/*   Updated: 2025/05/13 22:11:01 by erazumov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>

void	search_and_replace(char *str, char find, char replace)
{
	if (!str)
		return ;
	while (*str)
	{
		if (*str == find)
			*str = replace;
		write(1, str, 1);
		str++;
	}
}

int	main(int ac, char **av)
{
	if (ac != 4)
	{
		write(1, "\n", 1);
		exit(0);
	}
	if (av[2][1] != '\0' || av[3][1] != '\0')
	{
		write(1, "\n", 1);
		exit(0);
	}
	search_and_replace(av[1], av[2][0], av[3][0]);
	write(1, "\n", 1);
	return (0);
}
