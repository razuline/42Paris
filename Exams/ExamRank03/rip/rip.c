/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rip.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erazumov <erazumov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/13 16:30:32 by erazumov          #+#    #+#             */
/*   Updated: 2025/08/09 13:25:36 by erazumov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rip.h"

void	get_solutions(char *buff, int n, int idx, int balance, int open,
		int close)
{
	if (idx == n)
	{
		if (balance == 0 && open == 0 && close == 0)
			puts(buff);
		return ;
	}

	char	c = buff[idx];
	if (c == '(')
	{
		if (open > 0)
		{
			buff[idx] = ' ';
			get_solutions(buff, n, idx + 1, balance, open - 1, close);
			buff[idx] = '(';
		}
		get_solutions(buff, n, idx + 1, balance + 1, open, close);
	}
	else if (c == ')')
	{
		if (close > 0)
		{
			buff[idx] = ' ';
			get_solutions(buff, n, idx + 1, balance, open, close - 1);
			buff[idx] = ')';
		}
		if (balance > 0)
			get_solutions(buff, n, idx + 1, balance - 1, open, close);
	}
	else
		get_solutions(buff, n, idx + 1, balance, open, close);
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
	while (input[n])
		n++;
	if (n == 0)
	{
		write(1, "\n", 1);
		return (0);
	}

	char	buff[MAX_LEN];
	int		i = 0;

	while (i < n)
	{
		buff[i] = input[i];
		i++;
	}
	buff[n] = '\0';

	int		open = 0;
	int		close = 0;
	i = 0;
	while (i < n)
	{
		if (buff[i] == '(')
			open++;
		else if (buff[i] == ')')
		{
			if (open > 0)
				open--;
			else
				close++;
		}
		i++;
	}
	get_solutions(buff, n, 0, 0, open, close);
	return (0);
}
