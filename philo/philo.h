/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erazumov <erazumov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 11:40:18 by erazumov          #+#    #+#             */
/*   Updated: 2025/03/27 12:32:56 by erazumov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdlib.h>
# include <unistd.h>

typedef struct	s_philo
{
	pthread_t		philo_thread;
	int				philo_id;
	int				meals_eaten;
	u_int64_t		last_meal_time;
	pthread_mutex_t	*right_fork;
	pthread_mutex_t	*left_fork;
	struct s_data	*data;
}				t_philo;

typedef struct	s_data
{
	t_philo			*philos;
	pthread_mutex_t	*forks;
	u_int64_t		start_time;
	int				number_of_philosophers;
	int				time_to_eat;
	int				time_to_sleep;
	int				time_to_die;
	int				must_eat_count; /* -1: endless */
	int				someone_died; /* 1: smn died */
	int				philos_ate_enough; /* 1: all ate enough */
	pthread_mutex_t	meal_mutex;
	pthread_mutex_t	print_mutex;
}				t_data;


#endif