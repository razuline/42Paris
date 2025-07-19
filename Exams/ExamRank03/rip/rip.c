/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rip.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erazumov <erazumov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/13 16:30:32 by erazumov          #+#    #+#             */
/*   Updated: 2025/07/19 13:12:31 by erazumov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rip.h"

void	get_solutions(char *buf, int n, int idx, int balance, int left,
		int right)
{
	char	c;

	if (idx == n)
	{
		if (balance == 0 && left == 0 && right == 0)
		{
			buf[n] = 0;
			puts(buf);
		}
		return ;
	}
	c = buf[idx];
	if (c == '(')
	{
		// 1. Essayer de retirer la parenthèse
		if (left > 0)
		{
			buf[idx] = ' ';
			get_solutions(buf, n, idx + 1, balance, left - 1, right);
			buf[idx] = '('; // Backtrack : on la remet pour l'autre chemin
		}
		// 2. Essayer de garder la parenthèse
		get_solutions(buf, n, idx + 1, balance + 1, left, right);
	}
	else if (c == ')')
	{
		// 1. Essayer de retirer la parenthèse
		if (right > 0)
		{
			buf[idx] = ' ';
			get_solutions(buf, n, idx + 1, balance, left, right - 1);
			buf[idx] = ')'; // Backtrack
		}
		// 2. Essayer de garder la parenthèse (si valide)
		if (balance > 0)
			get_solutions(buf, n, idx + 1, balance - 1, left, right);
	}
	else // Pour les caractères qui ne sont pas des parenthèses (ex: espaces)
		get_solutions(buf, n, idx + 1, balance, left, right);
}

int	main(int ac, char **av)
{
	char	*input;
	int		i;
	int		n;
	int		left;
	int		right;

	if (ac != 2)
	{
		write(1, "\n", 1);
		return (0);
	}
	input = av[1];
	n = 0;
	while (input[n] != '\0')
		n++;
	if (n == 0)
		return (0);

	char	buf[n + 1];

	i = 0;
	while (i <= n)
	{
		buf[i] = input[i];
		i++;
	}
	
	left = 0;
	right = 0;
	i = 0;
	while (i < n)
	{
		if (buf[i] == '(')
			left++;
		else if (buf[i] == ')')
		{
			if (left > 0)
				left--;
			else
				right++;
		}
		i++;
	}
	get_solutions(buf, n, 0, 0, left, right);
	return (0);
}
