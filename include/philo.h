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
typedef struct s_input
{
	u_int32_t	philo_nr;
	u_int32_t	time_to_die;
	u_int32_t	time_to_eat;
	u_int32_t	time_to_sleep;
	u_int32_t	to_eat_nr;
}	t_input;

/**
 * @brief 
 * 
 */
typedef struct s_shared_data
{
	int32_t			*forks;
	pthread_mutex_t	lock;
	t_input			*input;
	u_int32_t		i;
}	t_shared_data;

// utilities
u_int32_t	ft_small_atoi(char *str);
size_t		ft_strlen(const char *str);

#endif
