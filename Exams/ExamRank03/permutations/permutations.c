/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   permutations.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erazumov <erazumov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/13 14:54:34 by erazumov          #+#    #+#             */
/*   Updated: 2025/07/17 16:02:23 by erazumov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "permutations.h"

int	ft_strlen(char *str)
{
	int	len;

	len = 0;
	while (str[len])
		len++;
	return (len);
}

void	ft_putstr(char *str)
{
	write(1, str, ft_strlen(str));
	write(1, "\n", 1);
}

void	ft_swap(char *a, char *b)
{
	char	tmp;

	tmp = *a;
	*a = *b;
	*b = tmp;
}

void	sort_str(char *str, int len)
{
	int	i;
	int	j;

	i = 0;
	while (i < len - 1)
	{
		j = i + 1;
		while (j < len)
		{
			if (str[i] > str[j])
				ft_swap(&str[i], &str[j]);
			j++;
		}
		i++;
	}
}

int	next_permutation(char *str, int len)
{
	int	i;
	int	j;
	int	left;
	int	right;
	
	i = len - 2;
	while (i >= 0 && str[i] >= str[i + 1])
		i--;
	if (i < 0)
		return (0);
	j = len - 1;
	while (str[j] <= str[i])
		j--;
	ft_swap(&str[i], &str[j]);
	left = i + 1;
	right = len - 1;
	while (left < right)
	{
		ft_swap(&str[left], &str[right]);
		left++;
		right--;
	}
	return (1);
}

int	main(int ac, char **av)
{
	int		i;
	int		len;
	char	*str;

	if (ac != 2)
	{
		write(1, "\n", 1);
		return (0);
	}
	len = ft_strlen(av[1]);
	str = malloc(len + 1);
	if (!str)
		return (1);
	i = 0;
	while (i < len)
	{
		str[i] = av[1][i];
		i++;
	}
	str[len] = '\0';
	sort_str(str, len);
	ft_putstr(str);
	while (next_permutation(str, len))
		ft_putstr(str);
	free(str);
	return (0);
}
