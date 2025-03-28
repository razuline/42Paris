/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erazumov <erazumov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 11:40:18 by erazumov          #+#    #+#             */
/*   Updated: 2025/03/28 11:30:04 by erazumov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>

# define SUCCESS 0
# define ERROR 1

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

/* Initialisation */
int		init_data(t_data *data, int ac, char **av);
int		simulation_start(t_data *data);
void	cleanup(t_data *data);

/* Utils */
int	ft_atoi(char *str);

#endif