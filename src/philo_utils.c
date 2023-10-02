/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   philo_utils.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: cschabra <cschabra@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/09/26 14:33:14 by cschabra      #+#    #+#                 */
/*   Updated: 2023/10/02 17:25:36 by cschabra      ########   odam.nl         */
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

bool	ft_print(t_shared_data *data, size_t philo, char *str)
{
	if (ft_check_if_dead(data))
		return (false);
	pthread_mutex_lock(&data->write);
	if (gettimeofday(&data->end, NULL) == -1)
		return (pthread_mutex_unlock(&data->write), \
			printf("time failed in print func"), false);
	printf(str, ft_return_ms(data), philo);
	pthread_mutex_unlock(&data->write);
	return (true);
}
