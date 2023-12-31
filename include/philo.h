/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   philo.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: cschabra <cschabra@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/09/14 16:02:10 by cschabra      #+#    #+#                 */
/*   Updated: 2023/10/05 19:25:10 by cschabra      ########   odam.nl         */
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

# define WRONGINPUT "Try: ./philo number_of_philosophers time_to_die time_to_eat \
	\n[Optional: number_of_times_each_philo_must_eat] \
	\nNo negatives or time_to > 99999 :)!\n"

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
 * @param max_eat Optional argument, if all philosophers have eaten at least
 * max_eat times, the simulation stops. If not specified, the simulation stops
 * when a philosopher dies.
 * 
 */
typedef struct s_init
{
	size_t			fork1;
	size_t			fork2;
	size_t			eaten;
	size_t			this_philo;
	u_int32_t		philo_nr;
	u_int32_t		time_to_die;
	u_int32_t		time_to_eat;
	u_int32_t		time_to_sleep;
	u_int32_t		max_eat;
}	t_init;

typedef struct s_shared_data
{
	size_t			this_philo;
	u_int32_t		philo_nr;
	u_int32_t		time_to_die;
	u_int32_t		time_to_eat;
	u_int32_t		time_to_sleep;
	u_int32_t		max_eat;
	int64_t			*last_meal;
	size_t			id;
	size_t			philo_died;
	int32_t			*done_eating;
	bool			died;
	bool			full;
	struct timeval	start;
	struct timeval	end;
	pthread_mutex_t	*forks;
	pthread_mutex_t	write;
	pthread_mutex_t	read;
	pthread_mutex_t	stop_lock;
}	t_shared_data;

typedef struct s_counters
{
	size_t	i;
	size_t	j;
	size_t	temp;
}	t_counters;

// checker
void		ft_checker(t_shared_data *data, u_int32_t die_time);

// mutexes
void		ft_destroy_mutexes(t_shared_data *data, u_int32_t amount);
bool		ft_create_mutexes(t_shared_data *data, u_int32_t amount);

// philo active
void		*ft_philo_loop(void *var);

// philo states
bool		ft_eating(t_shared_data *data, t_init *info, size_t fork1, \
	size_t fork2);
bool		ft_sleeping(t_shared_data *data, t_init *info, size_t fork1);
bool		ft_thinking(t_shared_data *data, size_t fork1);

// philo utilities
bool		ft_check_if_dead(t_shared_data *data);
bool		ft_print(t_shared_data *data, size_t philo, char *str);

// string utilities
bool		ft_death_array(t_shared_data *data);
bool		ft_full_array(t_shared_data *data);
u_int32_t	ft_small_atoi(char *str);
size_t		ft_strlen(const char *str);

// threads
bool		ft_prep_threads(t_shared_data *data);

// time utilities
int64_t		ft_time(t_shared_data *data);
bool		ft_usleep(t_shared_data *data, u_int32_t time);
int64_t		ft_return_ms(t_shared_data *data);

#endif
