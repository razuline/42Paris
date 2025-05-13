/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   union.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erazumov <erazumov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 21:20:28 by erazumov          #+#    #+#             */
/*   Updated: 2025/05/13 21:52:33 by erazumov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

void	union_chars(char *s1, char *s2)
{
	int	i;
	int	used[256] = {0};

	i = 0;
	while (s1[i])
	{
		if (used[(unsigned char)s1[i]] == 0)
		{
			write(1, &s1[i], 1);
			used[(unsigned char)s1[i]] = 1;
		}
		i++;
	}
	i = 0;
	while (s2[i])
	{
		if (used[(unsigned char)s2[i]] == 0)
		{
			write(1, &s2[i], 1);
			used[(unsigned char)s2[i]] = 1;
		}
		i++;
	}
}

int	main(int ac, char **av)
{
	if (ac == 3)
		union_chars(av[1], av[2]);
	write(1, "\n", 1);
	return (0);
}
