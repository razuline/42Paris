/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erazumov <erazumov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 11:00:33 by erazumov          #+#    #+#             */
/*   Updated: 2025/03/28 16:25:35 by erazumov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	simulation_start(t_data *data)
{
	
}

void	clear_data(t_data *data)
{
	if (data->number_of_philosophers)
		free(data->number_of_philosophers);
	if (data->forks)
		free(data->forks);
	if (data->philos)
		free(data->philos);
}
