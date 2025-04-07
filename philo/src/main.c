/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erazumov <erazumov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 10:38:02 by erazumov          #+#    #+#             */
/*   Updated: 2025/04/07 12:59:01 by erazumov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	main(int ac, char **av)
{
	t_data	data;

	if (ac < 5 || ac > 6)
	{
		printf("Error: wrong number of arguments\n");
		return (1);
	}
	if (init_data(&data, ac, av) == ERROR)
	{
		printf("Error: initialisation failed\n");
		return (1);
	}
	if (simulation_start(&data) == ERROR)
	{
		printf("Error: simulation failed\n");
		clear_data(&data);
		return (1);
	}
	clear_data(&data);
	return (0);
}
