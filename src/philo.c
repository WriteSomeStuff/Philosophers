/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   philo.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: cschabra <cschabra@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/09/26 11:55:49 by cschabra      #+#    #+#                 */
/*   Updated: 2023/09/26 17:05:21 by cschabra      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

bool	ft_create_philos(t_init *info)
{
	pthread_t		*threads;
	t_shared_data	data;
	size_t			i;
	size_t			j;
	int				temp;

	temp = 0;
	i = 0;
	j = 0;
	data.info = info;
	data.id = 0;
	data.died = false;
	gettimeofday(&info->start, NULL);
	if (ft_single_philo(info))
		return (true);
	threads = malloc((info->philo_nr) * sizeof(pthread_t));
	if (!threads)
		return (printf("threads malloc failed"), false);
	if (!ft_create_mutexes(&data, info->philo_nr))
		return (free(threads), printf("create mutexes failed"), false);
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
			free(threads);
			return (false);
		}
		if (info->philo_died)
		{
			temp = j;
			gettimeofday(&info->end, NULL);
		}
		j++;
	}
	if (temp)
		printf("%lld %d died", ft_return_msec(info), temp + 1);
	ft_destroy_mutexes(&data, info->philo_nr);
	free(data.forks);
	free(threads);
	if (i < info->philo_nr)
		return (printf("phtread create failed"), false);
	return (true);
}
