/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_str.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erazumov <erazumov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 18:40:56 by erazumov          #+#    #+#             */
/*   Updated: 2025/05/08 19:05:36 by erazumov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

void	expand_str(char *str)
{
	int	i;
	int	space_flag;

	i = 0;
	space_flag = 0;
	while (str[i] == ' ' || str[i] == '\t')
		i++;
	while (str[i])
	{
		if (str[i] == ' ' || str[i] == '\t')
			space_flag = 1;
		else
		{
			if (space_flag)
			{
				write(1, "   ", 3);
				space_flag = 0;
			}
			if (str[i] != ' ' && str[i] != '\t')
				write(1, &str[i], 1);
		}
		i++;
	}
}

int	main(int ac, char **av)
{
	if (ac == 2)
		expand_str(av[1]);
	write(1, "\n", 1);
	return (0);
}
