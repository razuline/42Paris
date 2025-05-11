/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotone.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erazumov <erazumov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/10 17:40:23 by erazumov          #+#    #+#             */
/*   Updated: 2025/05/11 11:37:46 by erazumov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

void	rotone(char *str)
{
	if (!str)
		return ;
	while (*str)
	{
		if (*str >= 'a' && *str <= 'y')
			*str += 1;
		else if (*str == 'z')
			*str = 'a';
		else if (*str >= 'A' && *str <= 'Y')
			*str += 1;
		else if (*str == 'Z')
			*str = 'A';
		write(1, &*str, 1);
		str++;
	}
}

int	main(int ac, char **av)
{
	if (ac == 2)
		rotone(av[1]);
	write(1, "\n", 1);
	return (0);
}
