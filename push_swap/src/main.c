/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erazumov <erazumov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/09 09:16:13 by erazumov          #+#    #+#             */
/*   Updated: 2025/04/09 13:13:03 by erazumov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../includes/push_swap.h"

int	main(int ac, char **av)
{
	t_stack *a;
	t_stack *b;

	if (ac < 2)
		return (0);
	a = init_stack();
	b = init_stack();
	parse_args(a, av);
	if (is_sorted(a))
	{
		free_stack(a);
		free_stack(b);
		return (0);
	}
	if (a->size <= 5)
		sort_small(a, b);
	else
		turk_sort(a, b);
	free_stack(a);
	free_stack(b);
	return (0);
}
