/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_str.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erazumov <erazumov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 18:40:56 by erazumov          #+#    #+#             */
/*   Updated: 2025/05/18 15:58:28 by erazumov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

void	expand_str(char *str)
{
	int	space_flag;

	space_flag = 0;
	while (*str == ' ' || *str == '\t')
		str++;

	while (*str)
	{
		if (*str == ' ' || *str == '\t')
			space_flag = 1;
		else
		{
			if (space_flag)
			{
				write(1, "   ", 3);
				space_flag = 0;
			}
			if (*str != ' ' && *str != '\t')
				write(1, str, 1);
		}
		str++;
	}
}

int	main(int ac, char **av)
{
	if (ac == 2)
		expand_str(av[1]);
	write(1, "\n", 1);
	return (0);
}
