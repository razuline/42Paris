/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rip.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erazumov <erazumov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/13 16:30:32 by erazumov          #+#    #+#             */
/*   Updated: 2025/07/26 17:15:56 by erazumov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rip.h"

void	get_solutions(char *buf, int n, int idx, int balance, int open,
		int close)
{
	char	c;

	if (idx == n)
	{
		if (balance == 0 && open == 0 && close == 0)
		{
			buf[n] = 0;
			puts(buf);
		}
		return ;
	}
	c = buf[idx];
	if (c == '(')
	{
		if (open > 0)
		{
			buf[idx] = ' ';
			get_solutions(buf, n, idx + 1, balance, open - 1, close);
			buf[idx] = '(';
		}
		get_solutions(buf, n, idx + 1, balance + 1, open, close);
	}
	else if (c == ')')
	{
		if (close > 0)
		{
			buf[idx] = ' ';
			get_solutions(buf, n, idx + 1, balance, open, close - 1);
			buf[idx] = ')';
		}
		if (balance > 0)
			get_solutions(buf, n, idx + 1, balance - 1, open, close);
	}
	else
		get_solutions(buf, n, idx + 1, balance, open, close);
}

int	main(int ac, char **av)
{
	if (ac != 2)
	{
		write(1, "\n", 1);
		return (0);
	}
	char	*input = av[1];
	int		n = 0;
	while (input[n] != '\0')
		n++;
	if (n == 0)
		return (0);

	char	buf[n + 1];

	int		i = 0;
	while (i <= n)
	{
		buf[i] = input[i];
		i++;
	}

	int		open = 0;
	int		close = 0;
	i = 0;
	while (i < n)
	{
		if (buf[i] == '(')
			open++;
		else if (buf[i] == ')')
		{
			if (open > 0)
				open--;
			else
				close++;
		}
		i++;
	}
	get_solutions(buf, n, 0, 0, open, close);
	return (0);
}
