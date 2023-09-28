/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   threads.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: cschabra <cschabra@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/09/26 11:55:49 by cschabra      #+#    #+#                 */
/*   Updated: 2023/09/28 19:26:07 by cschabra      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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

static void	ft_checker(t_shared_data *data)
{
	while (1)
	{
		pthread_mutex_lock(&data->stop_lock);
		if (data->died == true)
		{
			pthread_mutex_lock(&data->write);
			gettimeofday(&data->end, NULL);
			printf("%lld %zu died\n", ft_return_msec(data), data->philo_died);
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

static bool	ft_join_threads(t_shared_data *data, t_counters *count, \
	pthread_t *threads)
{
	count->j = 0;
	while (count->j < count->i)
	{
		if (pthread_join(threads[count->j], NULL))
		{
			ft_destroy_mutexes(data, data->philo_nr);
			free(data->forks);
			free(data->done_eating);
			free(threads);
			return (false);
		}
		count->j++;
	}
	return (true);
}

static bool	ft_create_treads(t_shared_data *data, t_counters *count, \
	pthread_t *threads)
{
	count->i = 0;
	if (!ft_create_mutexes(data, data->philo_nr))
		return (free(threads), free(data->done_eating), \
			printf("create mutex failed"), false);
	data->last_meal = ft_time();
	while (count->i < count->temp)
	{
		if (pthread_create(&threads[count->i], NULL, \
			&ft_philo_loop, (void *)data))
			break ;
		count->i++;
	}
	ft_checker(data);
	return (true);
}

bool	ft_prep_threads(t_shared_data *data)
{
	pthread_t	*threads;
	t_counters	count;

	count.temp = data->philo_nr;
	data->id = 0;
	data->died = false;
	data->full = false;
	gettimeofday(&data->start, NULL);
	threads = malloc(data->philo_nr * sizeof(pthread_t));
	if (!threads)
		return (printf("threads malloc failed"), false);
	if (!ft_int_array(data))
		return (printf("int array malloc failed"), free(threads), false);
	if (!ft_create_treads(data, &count, threads) || \
		!ft_join_threads(data, &count, threads))
		return (false);
	ft_destroy_mutexes(data, data->philo_nr);
	free(data->forks);
	free(data->done_eating);
	free(threads);
	if (count.i < data->philo_nr)
		return (printf("phtread create failed"), false);
	return (true);
}
