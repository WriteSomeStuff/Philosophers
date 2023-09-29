/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   philo_states.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: cschabra <cschabra@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/09/26 14:34:50 by cschabra      #+#    #+#                 */
/*   Updated: 2023/09/29 19:38:51 by cschabra      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	ft_unlock_forks(t_shared_data *data, size_t fork1, size_t fork2)
{
	pthread_mutex_unlock(&data->forks[fork1]);
	pthread_mutex_unlock(&data->forks[fork2]);
}

bool	ft_eating(t_shared_data *data, t_init *info, size_t fork1, size_t fork2)
{
	pthread_mutex_lock(&data->forks[fork2]);
	pthread_mutex_lock(&data->forks[fork1]);
	pthread_mutex_lock(&data->stop_lock);
	data->last_meal[info->this_philo] = ft_time();
	pthread_mutex_unlock(&data->stop_lock);
	if (ft_check_if_dead(data))
		return (ft_unlock_forks(data, fork1, fork2), false); // here or before last meal time is set?
	if (!ft_print(data, info->this_philo + 1, "%ld %zu has taken a fork\n") || \
		!ft_print(data, info->this_philo + 1, "%ld %zu has taken a fork\n") || \
		!ft_print(data, info->this_philo + 1, "%ld %zu is eating\n") || \
		!ft_usleep(data, info->time_to_eat))
		return (ft_unlock_forks(data, fork1, fork2), false);
	info->eaten++;
	if (info->max_eat && info->eaten == info->max_eat)
	{
		pthread_mutex_lock(&data->stop_lock);
		data->done_eating[info->this_philo] = 1;
		pthread_mutex_unlock(&data->stop_lock);
	}
	ft_unlock_forks(data, fork1, fork2);
	pthread_mutex_lock(&data->stop_lock);
	if (data->full == true)
		return (pthread_mutex_unlock(&data->stop_lock), false);
	pthread_mutex_unlock(&data->stop_lock);
	return (true);
}

bool	ft_sleeping(t_shared_data *data, t_init *info, size_t fork1)
{
	if (!ft_print(data, fork1 + 1, "%ld %zu is sleeping\n"))
		return (false);
	if (!ft_usleep(data, info->time_to_sleep))
		return (false);
	return (true);
}

bool	ft_thinking(t_shared_data *data, size_t fork1)
{
	if (!ft_print(data, fork1 + 1, "%ld %zu is thinking\n"))
		return (false);
	return (true);
}
