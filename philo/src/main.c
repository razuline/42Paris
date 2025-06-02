/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erazumov <erazumov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 10:38:02 by erazumov          #+#    #+#             */
/*   Updated: 2025/06/02 17:04:47 by erazumov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int ac, char **av)
{
	t_data	data;

	if (init_data(&data, ac, av) != SUCCESS)
		return (FAILURE);
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
