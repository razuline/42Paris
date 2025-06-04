/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erazumov <erazumov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 10:38:02 by erazumov          #+#    #+#             */
/*   Updated: 2025/06/04 16:32:59 by erazumov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int	main(int ac, char **av)
{
	t_data		data;
	t_errors	error;

	if (error = init_data(&data, ac, av) != SUCCESS)
		return (cleanup(&data), error);
	if (init_forks(&data) != SUCCESS)
		return (cleanup(&data), FAILURE);
	if (init_philos(&data) != SUCCESS)
		return (cleanup(&data), FAILURE);
	if (start_simulation(&data) != SUCCESS)
		return (cleanup(&data), FAILURE);
	monitor_simulation(&data);

	cleanup(&data);
	return (SUCCESS);
}
