/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erazumov <erazumov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 11:40:18 by erazumov          #+#    #+#             */
/*   Updated: 2025/06/02 15:36:07 by erazumov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdio.h>
# include <stdint.h>
# include <stdlib.h>
# include <string.h>
# include <sys/time.h>
# include <unistd.h>

# define SUCCESS 0
# define FAILURE 1

/* Philos' messages*/
# define TAKE_FORKS "has taken a fork"
# define THINKING "is thinking"
# define SLEEPING "is sleeping"
# define EATING "is eating"
# define DIED "died"

typedef struct s_philo
{
	int				id;
	pthread_t		thread;
	int				meals_eaten;
	uint64_t		last_meal_time;
	int				left_fork;
	int				right_fork;
	struct s_data	*data;
}			t_philo;

typedef struct s_data
{
	int				num_philos;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				max_meals;
	uint64_t		start_time;
	pthread_mutex_t	*forks;
	pthread_mutex_t	print_mutex;
	pthread_mutex_t	meal_mutex;
	t_philo			*philos;
	int				is_dead;
}			t_data;

/* Initialisation */
int			init_data(t_data *data, int ac, char **av);
int			init_forks(t_data *data);
int			init_philos(t_data *data);

/* Time (+ test) */
uint64_t	get_time_in_ms(void);
void		ft_sleep(uint64_t ms);

/* Actions */
void	*philo_routine(void *arg);
void	take_forks(t_philo *philo);
void	drop_forks(t_philo *philo);
void	eat(t_philo *philo);
void	sleep_and_think(t_philo *philo);

/* Simulations */
int		should_continue(t_data *data);
int		start_simulation(t_data *data);

/* Monitor */
void		monitor(t_data *data);
int			alloc_resources(t_data *data);

/* Utils */
void	print_status(t_philo *philo, char *status);
int		ft_atoi(char *str); /* (+ test) */
void	clear_data(t_data *data);

#endif
