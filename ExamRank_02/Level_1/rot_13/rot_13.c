/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rot_13.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erazumov <erazumov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/10 17:41:23 by erazumov          #+#    #+#             */
/*   Updated: 2025/05/11 11:46:35 by erazumov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

void	rot_13(char *str)
{
	if (!str)
		return ;
	while (*str)
	{
		if (*str >= 'A' && *str <= 'M')
			*str += 13;
		else if (*str >= 'N' && *str <= 'Z')
			*str -= 13;
		else if (*str >= 'a' && *str <= 'm')
			*str += 13;
		else if (*str >= 'n' && *str <= 'z')
			*str -= 13;
		write(1, &*str, 1);
		str++;
	}
}

int	main(int ac, char **av)
{
	if (ac == 2)
		rot_13(av[1]);
	write(1, "\n", 1);
	return (0);
}
