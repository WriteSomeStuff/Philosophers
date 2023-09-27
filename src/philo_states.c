/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   philo_states.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: cschabra <cschabra@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/09/26 14:34:50 by cschabra      #+#    #+#                 */
/*   Updated: 2023/09/26 17:04:16 by cschabra      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// bool	ft_nom()
// {
//		maybe try to pick up 1 fork, check if other fork available, if not, drop fork and return???
// }

int32_t	ft_eating(t_shared_data *data, t_init *info, size_t fork1, size_t fork2)
{
	pthread_mutex_lock(&data->forks[fork2]);
	pthread_mutex_lock(&data->forks[fork1]);
	data->forks_available[info->fork2] = 0;
	data->forks_available[info->fork1] = 0;
	info->last_meal = ft_time();
	if (ft_check_starvation(data, info))
	{
		pthread_mutex_unlock(&data->forks[fork1]);
		pthread_mutex_unlock(&data->forks[fork2]);
		return (1);
	}
	if (!ft_lock_n_print(data, fork1 + 1, "%lld %zu has taken a fork\n") || \
		!ft_lock_n_print(data, fork1 + 1, "%lld %zu has taken a fork\n") || \
		!ft_lock_n_print(data, fork1 + 1, "%lld %zu is eating\n") || \
		!ft_usleep(data, info->time_to_eat))
	{
		pthread_mutex_unlock(&data->forks[fork1]);
		pthread_mutex_unlock(&data->forks[fork2]);
		return (2);
	}
	info->eaten++;
	data->forks_available[info->fork1] = 1;
	data->forks_available[info->fork2] = 1;
	pthread_mutex_unlock(&data->forks[fork1]);
	pthread_mutex_unlock(&data->forks[fork2]);
	return (0);
}

bool	ft_sleeping(t_shared_data *data, t_init *info, size_t fork1)
{
	if (!ft_lock_n_print(data, fork1 + 1, "%lld %zu is sleeping\n"))
		return (false);
	if (!ft_usleep(data, info->time_to_sleep))
		return (false);
	return (true);
}

bool	ft_thinking(t_shared_data *data, size_t fork1)
{
	if (!ft_lock_n_print(data, fork1 + 1, "%lld %zu is thinking\n"))
		return (false);
	return (true);
}
