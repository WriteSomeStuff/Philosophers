/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   checker.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: cschabra <cschabra@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/09/29 19:53:15 by cschabra      #+#    #+#                 */
/*   Updated: 2023/09/29 20:05:56 by cschabra      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static bool	ft_all_alive(t_shared_data *data, u_int32_t die_time)
{
	size_t	i;
	int64_t	time;

	i = 0;
	while (i < data->philo_nr) // lock philo_nr? is copied in all threads but is only ever read and not written to..
	{
		time = ft_time() - data->last_meal[i];
		if (time >= die_time)
		{
			data->died = true;
			data->philo_died = i + 1;
			return (false);
		}
		i++;
	}
	return (true);
}

static bool	ft_all_full(t_shared_data *data)
{
	size_t	i;

	i = 0;
	while (i < data->philo_nr)
	{
		if (!data->done_eating[i])
			return (false);
		i++;
	}
	data->full = true;
	return (true);
}

void	ft_checker(t_shared_data *data, u_int32_t die_time)
{
	while (1)
	{
		pthread_mutex_lock(&data->stop_lock);
		if (!ft_all_alive(data, die_time))
		{
			pthread_mutex_lock(&data->write);
			gettimeofday(&data->end, NULL);
			printf("%ld %zu died\n", ft_return_msec(data), data->philo_died);
			pthread_mutex_unlock(&data->write);
			pthread_mutex_unlock(&data->stop_lock);
			break ;
		}
		else
		{
			if (ft_all_full(data))
			{
				pthread_mutex_unlock(&data->stop_lock);
				break ;
			}
		}
		pthread_mutex_unlock(&data->stop_lock);
		usleep(1000);
	}
}
