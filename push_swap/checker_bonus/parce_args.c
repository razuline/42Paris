/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parce_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erazumov <erazumov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 14:18:02 by erazumov          #+#    #+#             */
/*   Updated: 2025/03/10 14:20:39 by erazumov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "checker.h"

void	parse_args(t_stack **a, char **av)
{
	int		i;
	int		num;
	char	*arg;
	t_stack	*new_node;

	i = 1;
	while (av[i])
	{
		arg = av[i];
		num = ft_atoi(arg);
		if (num == 0 && ft_strcmp(arg, "0") != 0)
			error();
		new_node = (t_stack *)malloc(sizeof(t_stack));
		if (!new_node)
			error();
		new_node->value = num;
		new_node->next = *a;
		*a = new_node;
		i++;
	}
}
