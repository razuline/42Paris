/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_capitalizer.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erazumov <erazumov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 20:28:12 by erazumov          #+#    #+#             */
/*   Updated: 2025/05/18 17:15:50 by erazumov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

void	str_capitalizer(char *str)
{
	int	new_word;

	new_word = 1;
	while (*str)
	{
		if (*str == ' ' || *str == '\t')
		{
			new_word = 1;
			write(1, str, 1);
		}
		else
		{
			if (new_word)
			{
				if (*str >= 'a' && *str <= 'z')
					write(1, &(char){*str - 32}, 1);
				else
					write(1, str, 1);
				new_word = 0;
			}
			else
			{
				if (*str >= 'A' && *str <= 'Z')
					write(1, &(char){*str + 32}, 1);
				else
					write(1, str, 1);
			}
		}
		str++;
	}
}

int	main(int ac, char **av)
{
	int	i;

	if (ac < 2)
		write(1, "\n", 1);
	i = 1;
	while (i < ac)
	{
		str_capitalizer(av[i]);
		write(1, "\n", 1);
		i++;
	}
	return (0);
}
