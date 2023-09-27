/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   threads.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: cschabra <cschabra@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/09/26 11:55:49 by cschabra      #+#    #+#                 */
/*   Updated: 2023/09/26 17:57:58 by cschabra      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

bool	ft_prep_threads(t_init *info)
{
	pthread_t		*threads;
	t_shared_data	data;
	size_t			i;
	size_t			j;
	size_t			temp;

	temp = 0;
	i = 0;
	j = 0;
	data.info = info;
	data.id = 0;
	data.died = false;
	gettimeofday(&info->start, NULL);
	if (ft_single_philo(info))
		return (true);
	threads = malloc(info->philo_nr * sizeof(pthread_t));
	if (!threads)
		return (printf("threads malloc failed"), false);
	if (!ft_int_array(&data, info))
		return (printf("int array malloc failed"), free(threads), false);
	if (!ft_create_mutexes(&data, info->philo_nr))
		return (free(threads), free(data.forks_available), printf("create mutexes failed"), false);
	info->last_meal = ft_time();
	while (i < info->philo_nr)
	{
		if (pthread_create(&threads[i], NULL, &ft_philo_loop, (void *)&data))
			break ;
		i++;
	}
	while (j < i)
	{
		if (pthread_join(threads[j], &info->philo_died))
		{
			ft_destroy_mutexes(&data, info->philo_nr);
			free(data.forks);
			free(data.forks_available);
			free(threads);
			return (false);
		}
		if (info->philo_died && !temp)
		{
			temp = j;
			gettimeofday(&info->end, NULL);
		}
		j++;
	}
	ft_destroy_mutexes(&data, info->philo_nr);
	free(data.forks);
	free(data.forks_available);
	free(threads);
	if (temp)
		printf("%lld %lu died\n", ft_return_msec(info), temp + 1);
	if (i < info->philo_nr)
		return (printf("phtread create failed"), false);
	return (true);
}

// new funcs that segv
// bool	ft_join_threads(t_shared_data *data, t_init *info, pthread_t *threads)
// {
// 	size_t	j;
// 	size_t	temp;

// 	j = 0;
// 	temp = 0;
// 	while (j < info->i)
// 	{
// 		if (pthread_join(threads[j], &info->philo_died))
// 		{
// 			ft_destroy_mutexes(data, info->philo_nr);
// 			free(data->forks);
// 			free(threads);
// 			return (false);
// 		}
// 		if (info->philo_died)
// 		{
// 			temp = j;
// 			gettimeofday(&info->end, NULL);
// 		}
// 		j++;
// 	}
// 	if (temp)
// 		printf("%lld %zu died", ft_return_msec(info), temp + 1);
// 	return (true);
// }

// bool	ft_create_treads(t_shared_data *data, t_init *info, pthread_t *threads)
// {
// 	if (!ft_create_mutexes(data, info->philo_nr))
// 		return (free(threads), printf("create mutexes failed"), false);
// 	info->last_meal = ft_time();
// 	while (info->i < info->philo_nr)
// 	{
// 		if (pthread_create(&threads[info->i], NULL, &ft_philo_loop, (void *)&data))
// 			break ;
// 		info->i++;
// 	}
// 	return (true);
// }

// bool	ft_prep_threads(t_init *info)
// {
// 	pthread_t		*threads;
// 	t_shared_data	data;

// 	data.info = info;
// 	data.id = 0;
// 	data.died = false;
// 	threads = malloc((info->philo_nr) * sizeof(pthread_t));
// 	if (!threads)
// 		return (printf("threads malloc failed"), false);
// 	gettimeofday(&info->start, NULL);
// 	if (ft_single_philo(info))
// 		return (true);
// 	if (!ft_create_treads(&data, info, threads) || \
// 		!ft_join_threads(&data, info, threads))
// 		return (false);
// 	ft_destroy_mutexes(&data, info->philo_nr);
// 	free(data.forks);
// 	free(threads);
// 	if (info->i < info->philo_nr)
// 		return (printf("phtread create failed"), false);
// 	return (true);
// }
