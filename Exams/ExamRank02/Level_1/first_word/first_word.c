/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   first_word.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erazumov <erazumov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/10 17:47:23 by erazumov          #+#    #+#             */
/*   Updated: 2025/05/13 22:09:25 by erazumov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

int	main(int ac, char **av)
{
	char	*str;

	if (ac != 2)
	{
		write(1, "\n", 1);
		return (0);
	}
	str = av[1];
	while (*str == ' ' || *str == '\t')
		str++;
	while (*str != '\0' && *str != ' ' && *str != '\t')
	{
		write(1, str, 1);
		str++;
	}
	write(1, "\n", 1);
	return (0);
}
