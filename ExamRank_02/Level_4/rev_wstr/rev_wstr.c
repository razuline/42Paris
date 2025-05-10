/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rev_wstr.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erazumov <erazumov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/10 11:59:03 by erazumov          #+#    #+#             */
/*   Updated: 2025/05/10 14:07:30 by erazumov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

void	rev_wstr(char *str)
{
	int	i;
	int	j;
	int	w_start;
	int	w_end;

	i = 0;
	w_end = 0;
	
	while (str[i])
		i++;
	w_end = i - 1;
	
	while (i >= 0)
	{
		if (str[i] != ' ')
		{
			w_start = i;
			while (w_start >= 0 && str[w_start] != ' ')
				w_start--;

			j = w_start + 1;
			while (j <= w_end)
				write(1, &str[j++], 1);

			if (w_start > 0)
				write(1, " ", 1);

			w_end = w_start - 1;
			i = w_start;
		}
		i--;
	}
}

int	main(int ac, char **av)
{
	if (ac == 2)
		rev_wstr(av[1]);
	write(1, "\n", 1);
	return (0);
}
