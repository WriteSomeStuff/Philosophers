/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   philo_utils.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: cschabra <cschabra@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/09/26 14:33:14 by cschabra      #+#    #+#                 */
/*   Updated: 2023/09/26 16:05:14 by cschabra      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

bool	ft_check_if_dead(t_shared_data *data)
{
	pthread_mutex_lock(&data->death);
	if (!data->died)
	{
		pthread_mutex_unlock(&data->death);
		return (false);
	}
	pthread_mutex_unlock(&data->death);
	return (true);
}

bool	ft_check_starvation(t_shared_data *data, t_init *info)
{
	long long int	time;

	time = ft_time() - info->last_meal;
	if (time >= info->time_to_die)
	{
		pthread_mutex_lock(&data->read);
		data->died = true;
		pthread_mutex_unlock(&data->read);
		return (true);
	}
	return (false);
}

bool	ft_lock_n_print(t_shared_data *data, size_t philo, char *str)
{
	t_init	*info;

	if (ft_check_if_dead(data))
		return (false);
	pthread_mutex_lock(&data->write);
	info = data->info;
	gettimeofday(&info->end, NULL);
	printf(str, ft_return_msec(info), philo);
	pthread_mutex_unlock(&data->write);
	return (true);
}
