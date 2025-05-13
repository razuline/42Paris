/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   repeat_alpha.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erazumov <erazumov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/10 17:42:48 by erazumov          #+#    #+#             */
/*   Updated: 2025/05/13 22:10:12 by erazumov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

void	repeat_alpha(char *str)
{
	int	count;

	count = 0;
	while (*str)
	{
		if (*str >= 'A' && *str <= 'Z')
		{
			count = *str - 'A' + 1;
			while (count--)
				write(1, str, 1);
		}
		else if (*str >= 'a' && *str <= 'z')
		{
			count = *str - 'a' + 1;
			while (count--)
				write(1, str, 1);
		}
		else
			write(1, str, 1);
		str++;
	}
}

int	main(int ac, char **av)
{
	if (ac == 2)
		repeat_alpha(av[1]);
	write(1, "\n", 1);
	return (0);
}
