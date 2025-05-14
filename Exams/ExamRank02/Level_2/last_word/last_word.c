/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   last_word.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erazumov <erazumov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 20:18:41 by erazumov          #+#    #+#             */
/*   Updated: 2025/05/13 20:48:18 by erazumov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

void	last_word(char *str)
{
	int	end;

	end = 0;
	while (str[end])
		end++;
	while (end >= 0 && (str[end] == ' ' || str[end] == '\t' || str[end] == '\0'))
		end--;
	while (end >= 0 && str[end] != ' ' && str[end] != '\t')
		end--;
	end++;
	while (str[end] && str[end] != ' ' && str[end] != '\t')
		write(1, &str[end++], 1);
}

int	main(int ac, char **av)
{
	if (ac == 2)
		last_word(av[1]);
	write(1, "\n", 1);
	return (0);
}
