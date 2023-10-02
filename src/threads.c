/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   threads.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: cschabra <cschabra@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/09/26 11:55:49 by cschabra      #+#    #+#                 */
/*   Updated: 2023/10/02 17:21:20 by cschabra      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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
			free(data->last_meal);
			return (false);
		}
		count->j++;
	}
	return (true);
}

static bool	ft_create_treads(t_shared_data *data, t_counters *count, \
	pthread_t *threads)
{
	u_int32_t	die_time;

	die_time = data->time_to_die;
	count->i = 0;
	if (!ft_death_array(data))
		return (free(threads), free(data->done_eating), \
			printf("death array failed"), false);
	if (!ft_create_mutexes(data, data->philo_nr))
		return (free(threads), free(data->done_eating), \
			free(data->last_meal), printf("create mutex failed"), false);
	while (count->i < count->temp)
	{
		if (pthread_create(&threads[count->i], NULL, \
			&ft_philo_loop, (void *)data))
			break ;
		count->i++;
	}
	ft_checker(data, die_time);
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
	threads = malloc(data->philo_nr * sizeof(pthread_t));
	if (!threads || gettimeofday(&data->start, NULL) == -1)
		return (printf("malloc or time failed"), false);
	if (!ft_full_array(data))
		return (printf("int array malloc failed"), free(threads), false);
	if (!ft_create_treads(data, &count, threads) || \
		!ft_join_threads(data, &count, threads))
		return (false);
	ft_destroy_mutexes(data, data->philo_nr);
	free(data->forks);
	free(data->done_eating);
	free(threads);
	free(data->last_meal);
	if (count.i < data->philo_nr)
		return (printf("phtread create failed"), false);
	return (true);
}
