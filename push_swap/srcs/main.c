/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erazumov <erazumov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 11:08:29 by erazumov          #+#    #+#             */
/*   Updated: 2025/03/05 11:20:39 by erazumov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "push_swap.h"

int	main(int ac, char **av)
{
	t_stack *a, *b = NULL;

	if (ac < 2)
		return (ft_printf("Usage: ./push_swap <numbers>\n"), 1);

	a = sort_input(ac, av);
	if (!a)
		return (1);

	ft_printf("Initial stack:\n");
	print_stack(a);

	// Testing stack operations
	sa(&a);
	pb(&a, &b);
	ra(&a);
	rra(&a);
	pa(&a, &b);

	ft_printf("Final stack:\n");
	print_stack(a);

	free_if_error(&a);
	free_if_error(&b);
	return (0);
}

