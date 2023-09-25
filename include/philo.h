/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   philo.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: cschabra <cschabra@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/09/14 16:02:10 by cschabra      #+#    #+#                 */
/*   Updated: 2023/09/19 14:47:35 by cschabra      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <sys/param.h>
# include <string.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>
# include <stdbool.h>
# include <limits.h>

# define WRONGINPUT "Try: ./philo number_of_philosophers time_to_die time_to_eat time_to_sleep \
	\n[Optional: number_of_times_each_philo_must_eat]\nNo negatives or time_to > 9999 :)!\n"

/**
 * @brief User input given which the program will use. 
 * All time_to variables are in milliseconds.
 * 
 * @param philo_nr Amount of philosophers and forks to create.
 * @param time_to_die If a philosopher didn’t start eating time_to_die 
 * milliseconds since the beginning of their last meal or since the start,
 * they die.
 * @param time_to_eat the time it takes for a philosopher to eat.
 * During that time, they will need to hold two forks.
 * @param time_to_sleep The time a philosopher will spend sleeping.
 * @param to_eat_nr Optional argument, if all philosophers have eaten at least
 * to_eat_nr times, the simulation stops. If not specified, the simulation stops
 * when a philosopher dies.
 * 
 */
typedef struct s_init
{
	u_int32_t		philo_nr;
	u_int32_t		time_to_die;
	u_int32_t		time_to_eat;
	u_int32_t		time_to_sleep;
	u_int32_t		to_eat_nr;
	u_int64_t		last_meal;
	void			*philo_died;
	struct timeval	start;
	struct timeval	end;
}	t_init;

/**
 * @brief 
 * 
 */
typedef struct s_shared_data
{
	pthread_mutex_t	*forks;
	pthread_mutex_t	write;
	pthread_mutex_t	read;
	pthread_mutex_t	death;
	t_init			*info;
	bool			died;
	size_t			id;
}	t_shared_data;

// mutexes
void		ft_destroy_mutexes(t_shared_data *data, u_int32_t amount);
bool		ft_create_mutexes(t_shared_data *data, u_int32_t amount);

// philo's
bool		ft_check_if_dead(t_shared_data *data);
bool		ft_create_philos(t_init *info);

// string utilities
u_int32_t	ft_small_atoi(char *str);
size_t		ft_strlen(const char *str);

// timestamp utilities
u_int64_t	ft_time(void);
bool		ft_usleep(t_shared_data *data, u_int32_t time);
u_int64_t	ft_return_msec(t_init *info);

#endif
