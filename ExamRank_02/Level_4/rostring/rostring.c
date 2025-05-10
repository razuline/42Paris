/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rostring.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erazumov <erazumov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/10 13:02:02 by erazumov          #+#    #+#             */
/*   Updated: 2025/05/10 13:52:59 by erazumov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

void	rostring(char *str)
{
	int	i;
	int	start;
	int	end;

	i = 0;
	while (str[i] == ' ' || str[i] == '\t')
		i++;
	start = i;
	while (str[i] && str[i] != ' ' && str[i] != '\t')
		i++;
	end = i;
	while (str[i] == ' ' || str[i] == '\t')
		i++;

	while (str[i])
	{
		if (str[i] != ' ' && str[i] != '\t')
		{
			if (i > 0 && (str[i - 1] == ' ' || str[i - 1] == '\t'))
				write(1, " ", 1);
			write(1, &str[i], 1);
		}
		i++;
	}
	if (start != end)
	{
		if (i > end)
			write(1, " ", 1);
		write(1, &str[start], end - start);
	}
}

int	main(int ac, char **av)
{
	if (ac >= 2)
		rostring(av[1]);
	write(1, "\n", 1);
	return (0);
}
