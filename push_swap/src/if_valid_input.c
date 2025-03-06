/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   if_valid_input.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erazumov <erazumov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 11:51:19 by erazumov          #+#    #+#             */
/*   Updated: 2025/03/06 13:27:47 by erazumov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "push_swap.h"

static int	is_digit(const char *str)
{
	
	if (*str == '-' || *str == '+')
		str++;
	if (!*str)
		return (0);
	while (*str)
	{
		if (*str < '0' || *str > '9')
			return (0);
		str++;
	}
	return (1);
}

static int	safe_atoi(char *str, int *error)
{
	int		i;
	int		sign;
	long	nbr;

	i = 0;
	sign = 1;
	nbr = 0;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign = -1;
		i++;
	}
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9') 
			return (*error = 1, 0);
		nbr = nbr * 10 + (str[i] - '0');
		if ((sign * nbr) > 2147483647 || (sign * nbr) < -2147483648)
			return (*error = 1, 0);
		i++;
	}	
	return ((int)(sign * nbr));
}

static int	check_dup(int *arr, int size, int num)
{
	int i;

	i = 0;
	while (i < size)
	{
		if (arr[i] == num)
				return (1);
		i++;
	}
	return (0);
}

int	*if_valid_input(int ac, char **av, int *size)
{
	int		i;
	int		nbr;
	int		error;
	int		*stack;

	*size = 0;
	stack = (int *)malloc(sizeof(int) * (ac - 1));
	if (!stack)
		return (NULL);
	i = 1;
	while (i < ac)
	{
		error = 0;
		nbr = safe_atoi(av[i], &error);
		if (error || check_dup(stack, *size, nbr))
			return (free(stack), NULL);
		stack[(*size)++] = nbr;
		i++;
	}
	return (stack);
}

/* TEST 
int	main(int ac, char **av)
{
	int	i;
	int	size;
	int	error;
	int	*stack;

	error = 0;
	stack = sort_input(ac, av, &size);
	if (!stack)
	{
		ft_printf("Error!\n");
		return (1);
	}
	ft_printf("Parsed stack: ");
	for (i = 0; i < size; i++)
		ft_printf("%d ", stack[i]);
	ft_printf("\n");

	free(stack);
	return (0);
}
*/