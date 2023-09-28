/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   philo_utils.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: cschabra <cschabra@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/09/26 14:33:14 by cschabra      #+#    #+#                 */
/*   Updated: 2023/09/28 18:05:39 by cschabra      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

bool	ft_check_if_dead(t_shared_data *data)
{
	pthread_mutex_lock(&data->stop_lock);
	if (!data->died)
	{
		pthread_mutex_unlock(&data->stop_lock);
		return (false);
	}
	pthread_mutex_unlock(&data->stop_lock);
	return (true);
}

bool	ft_check_starvation(t_shared_data *data, t_init *info)
{
	long long int	time;

	time = ft_time() - info->last_meal;
	if (time >= info->time_to_die)
	{
		pthread_mutex_lock(&data->stop_lock);
		data->died = true;
		data->philo_died = info->this_philo + 1;
		pthread_mutex_unlock(&data->stop_lock);
		return (true);
	}
	return (false);
}

bool	ft_print(t_shared_data *data, size_t philo, char *str)
{
	if (ft_check_if_dead(data))
		return (false);
	pthread_mutex_lock(&data->write);
	gettimeofday(&data->end, NULL);
	printf(str, ft_return_msec(data), philo);
	pthread_mutex_unlock(&data->write);
	return (true);
}
