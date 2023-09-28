/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   philo_states.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: cschabra <cschabra@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/09/26 14:34:50 by cschabra      #+#    #+#                 */
/*   Updated: 2023/09/28 19:02:43 by cschabra      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

bool	ft_eating(t_shared_data *data, t_init *info, size_t fork1, size_t fork2)
{
	pthread_mutex_lock(&data->forks[fork2]);
	pthread_mutex_lock(&data->forks[fork1]);
	info->last_meal = ft_time();
	if (ft_check_starvation(data, info) || \
		!ft_print(data, info->this_philo + 1, "%lld %zu has taken a fork\n") || \
		!ft_print(data, info->this_philo + 1, "%lld %zu has taken a fork\n") || \
		!ft_print(data, info->this_philo + 1, "%lld %zu is eating\n") || \
		!ft_usleep(data, info->time_to_eat))
		return (pthread_mutex_unlock(&data->forks[fork1]), \
			pthread_mutex_unlock(&data->forks[fork2]), false);
	info->eaten++;
	if (info->max_eat && info->eaten == info->max_eat)
	{
		pthread_mutex_lock(&data->stop_lock);
		data->done_eating[info->this_philo] = 1;
		pthread_mutex_unlock(&data->stop_lock);
	}
	pthread_mutex_unlock(&data->forks[fork1]);
	pthread_mutex_unlock(&data->forks[fork2]);
	pthread_mutex_lock(&data->stop_lock);
	if (data->full == true)
		return (pthread_mutex_unlock(&data->stop_lock), false);
	pthread_mutex_unlock(&data->stop_lock);
	return (true);
}

bool	ft_sleeping(t_shared_data *data, t_init *info, size_t fork1)
{
	if (!ft_print(data, fork1 + 1, "%lld %zu is sleeping\n"))
		return (false);
	if (!ft_usleep(data, info->time_to_sleep))
		return (false);
	return (true);
}

bool	ft_thinking(t_shared_data *data, size_t fork1)
{
	if (!ft_print(data, fork1 + 1, "%lld %zu is thinking\n"))
		return (false);
	return (true);
}
