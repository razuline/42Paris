/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   permutations_bits.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erazumov <erazumov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/20 19:54:05 by erazumov          #+#    #+#             */
/*   Updated: 2025/07/20 20:01:55 by erazumov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "permutations_bits.h"

void	perm(int *cnt, int n, int depth, char *buf)
{
	int	c;

	if (depth == n)
	{
		buf[n] = '\0';
		puts(buf);
		return ;
	}
	c = 0;
	while (c < 256)
	{
		if (cnt[c])
		{
			buf[depth] = (char)c;
			--cnt[c];
			perm(cnt, n , depth + 1, buf);
			++cnt[c];
		}
		c++;
	}
}

int	main(int ac, char **av)
{
	if (ac == 2 && av[1][0])
	{
		int		i;
		int		n;
		int		cnt[256] = {0};
		char	*buf;

		n = strlen(av[1]);
		buf = malloc(n + 1);
		if (!buf)
			return (1);
		i = 0;
		while (i < n)
		{
			++cnt[(unsigned char)av[1][i]];
			i++;
		}
		perm(cnt, n, 0, buf);
		free(buf);
	}
	return (0);
}
