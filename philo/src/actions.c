/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erazumov <erazumov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 11:00:33 by erazumov          #+#    #+#             */
/*   Updated: 2025/04/05 10:29:11 by erazumov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	philo_eat(t_philo *philo)
{
	if (!should_continue(philo->data))
		return ;
	usleep(100);
	pthread_mutex_lock(&philo->data->meal_mutex);
	philo->last_meal_time = get_time();
	philo->meals_eaten++;
	if (philo->data->must_eat_count != -1
		&& philo->meals_eaten >= philo->data->must_eat_count)
		philo->data->philos_ate_enough = 1;
	pthread_mutex_unlock(&philo->data->meal_mutex);
	print_status(philo, EATING);
	ft_sleep(philo->data->time_to_eat);
}

void	philo_sleep(t_philo *philo)
{
	if (!should_continue(philo->data))
		return ;
	print_status(philo, SLEEPING);
	ft_sleep(philo->data->time_to_sleep);
}

void	philo_think(t_philo *philo)
{
	if (!should_continue(philo->data))
		return ;
	print_status(philo, THINKING);
}
