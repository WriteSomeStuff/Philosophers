/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   mutexes.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: cschabra <cschabra@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/09/26 11:55:42 by cschabra      #+#    #+#                 */
/*   Updated: 2023/10/02 17:15:33 by cschabra      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_destroy_mutexes(t_shared_data *data, u_int32_t amount)
{
	size_t	i;

	i = 0;
	while (i < amount)
	{
		if (pthread_mutex_destroy(&data->forks[i]))
			printf("forks mutex destroy error");
		i++;
	}
	if (pthread_mutex_destroy(&data->write))
		printf("write mutex destroy error");
	if (pthread_mutex_destroy(&data->read))
		printf("read mutex destroy error");
	if (pthread_mutex_destroy(&data->stop_lock))
		printf("death mutex destroy error");
}

bool	ft_create_mutexes(t_shared_data *data, u_int32_t amount)
{
	size_t	i;

	i = 0;
	if (pthread_mutex_init(&data->write, NULL))
		return (false);
	if (pthread_mutex_init(&data->stop_lock, NULL))
		return (pthread_mutex_destroy(&data->write), false);
	if (pthread_mutex_init(&data->read, NULL))
		return (pthread_mutex_destroy(&data->write), \
			pthread_mutex_destroy(&data->stop_lock), false);
	data->forks = malloc(amount * sizeof(pthread_mutex_t));
	if (!data->forks)
		return (ft_destroy_mutexes(data, i), false);
	while (i < amount)
	{
		if (pthread_mutex_init(&data->forks[i], NULL))
			return (ft_destroy_mutexes(data, i), free(data->forks), \
				false);
		i++;
	}
	return (true);
}
