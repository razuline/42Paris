/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erazumov <erazumov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/09 09:16:13 by erazumov          #+#    #+#             */
/*   Updated: 2025/04/12 12:50:37 by erazumov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	main(int ac, char **av)
{
	t_stack	a;
	t_stack	b;

	if (ac < 2)
		return (0);
	parse_args(&a, &b, av);
	if (is_sorted(&a))
	{
		free_stack(&a);
		return (0);
	}
	if (a.size <= 5)
		small_sort(&a, &b);
	chunk_sort(&a, &b);
	free_stack(&a);
	return (0);
}
