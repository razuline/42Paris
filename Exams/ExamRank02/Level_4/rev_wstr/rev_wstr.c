/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rev_wstr.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erazumov <erazumov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/10 11:59:03 by erazumov          #+#    #+#             */
/*   Updated: 2025/05/14 16:36:52 by erazumov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

void	rev_wstr(char *str)
{
	int	start;
	int	end;

	end = 0;
	while (str[end])
		end++;
	end--;

	while (end >= 0)
	{
		if (str[end] == ' ' || str[end] == '\t')
			end--;
		else
		{
			start = end;
			while (start >= 0 && str[start] != ' ' && str[start] != '\t')
				start--;
			write(1, &str[start + 1], end - start);

			if (start > 0)
				write(1, " ", 1);

			end = start;
		}
	}
}

int	main(int ac, char **av)
{
	if (ac == 2)
		rev_wstr(av[1]);
	write(1, "\n", 1);
	return (0);
}
