/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   time_utils.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: cschabra <cschabra@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/09/26 11:55:53 by cschabra      #+#    #+#                 */
/*   Updated: 2023/09/29 18:44:39 by cschabra      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int64_t	ft_time(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return (((time.tv_sec * 1000000) + time.tv_usec) / 1000);
}

bool	ft_usleep(t_shared_data *data, u_int32_t ms)
{
	int64_t	start;

	start = ft_time();
	while ((ft_time() - start) <= ms)
	{
		if (ft_check_if_dead(data))
			return (false);
		usleep(100);
	}
	return (true);
}

int64_t	ft_return_msec(t_shared_data *data)
{
	return ((((data->end.tv_sec - data->start.tv_sec) * 1000000) + \
		(data->end.tv_usec - data->start.tv_usec)) / 1000);
}
