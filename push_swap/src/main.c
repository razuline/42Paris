/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erazumov <erazumov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/09 09:16:13 by erazumov          #+#    #+#             */
/*   Updated: 2025/04/10 18:22:49 by erazumov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	main(int ac, char **av)
{
	t_stack	a;
	t_stack	b;

	if (ac < 2)
		return (0);
	ft_memset(&a, 0, sizeof(t_stack));
	ft_memset(&b, 0, sizeof(t_stack));
	parse_args(&a, av);
	if (is_sorted(&a))
	{
		free_stack(&a);
		return (0);
	}
	if (a.size <= 5)
		small_sort(&a, &b);
	else
		chunk_sort(&a, &b);
	free_stack(&a);
	return (0);
}
