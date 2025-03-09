/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erazumov <erazumov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 18:30:58 by erazumov          #+#    #+#             */
/*   Updated: 2025/03/09 09:15:20 by erazumov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../push_swap.h"

void	if_error(const char *str)
{
	if (str)
		write(2, str, ft_strlen(str));
	write(2, "\n", 1);
	exit(1);
}

void	parse_args(t_stack *a, char **av)
{
	int	i;
	int	value;

	i = 1;
	while (av[i])
	{
		value = ft_atoi(av[i]);
		push_to(a, value);
		i++;
	}
}

