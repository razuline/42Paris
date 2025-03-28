/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erazumov <erazumov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 10:38:02 by erazumov          #+#    #+#             */
/*   Updated: 2025/03/28 12:05:38 by erazumov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	main(int ac, char **av)
{
	t_data	data;

	
	if (ac < 5 || ac > 6) /* !!! Checking the input */
	{
		printf("Error: wrong number of arguments\n");
		return (1);
	}
	if (init_data(&data, ac, av) == ERROR) /* !!! Initialisation */
	{
		printf("Error: initialisation failed\n");
		return (1);
	}
	if (simulation_start(&data) == ERROR) /* !!! Launch of simulation*/
	{
		printf("Error: simulation failed\n");
		cleanup(&data);
		return (1);
	}
	cleanup(&data); /* !!! Clean up all the resources */
	return (0);
}
