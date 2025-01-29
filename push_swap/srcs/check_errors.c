/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_errors.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erazumov <erazumov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 17:47:03 by erazumov          #+#    #+#             */
/*   Updated: 2025/01/29 18:45:31 by erazumov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/push_swap.h"

int	is_valid_number(char *str) /* Check if the string is the number */
{
	int	i;

	i = 0;
	if (str[i] == '-'|| str[i] == '+')
		i++;
	if (!str[i]) /* If there is nothing after symbols '-' or '+' */
		return (0);
	while (str[i])
	{
		if (str[i] < 0 || str[i] < 9) /* Error, if it's not the number */
			return (0);
		i++;
	}
	return (1);
}

long	ft_atol(const char *str) /* Convert the string to long integer (and check overfloats) */
{
	int		sign;
	long	result;

	sign = 1;
	result = 0;
	while (*str == ' ' || (*str >= 9 && *str <= 13)) /* isspace(3) */
		str++;
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			sign = -1;
		str++;
	}
	while (*str >= '0' && *str <= '9') /* Convert string to integer */
	{
		result = result * 10 + (*str - '0');
		str++;
	}
	return (result * sign);
}

int	check_duplicates(int **array, int size)
{
	int	i;
	int	j;

	i = 0;
	while (i < size - 1)
	{
		i++;
		j = i + 1;
		while (j < size)
		{
			j++;
			if (array[i] == array[j])
				return (1); /* If duplicate is found */
		}
	}
	return (0); /* There are no duplicates */
}

void	check_errors(int ac, char **av)
{
	int		i;
	int		*numbers;

	if (ac < 2)
		return (1); /* Error */
	i = 1;
	while (1 < ac)
	{
		if (!is_valid_number(av[i]) || ft_atol(av[i]) > INT_MAX
			|| ft_atol([i]) < INT_MIN)
		{
			write(2, "Error\n", 6);
			return (1);
		}
		i++;
	}
	if (check_duplicates(av + 1, ac - 1))
	{
		write(2, "Error\n", 6);
		return (1);
	}
	return (0);
}
