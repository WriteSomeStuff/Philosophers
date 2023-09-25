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

static bool	ft_lock_n_print(t_shared_data *data, size_t philo, char *str)
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

static void	*ft_philo_loop(void *var)
{
	t_shared_data	*data;
	t_init			info;
	size_t			fork1;
	size_t			fork2;
	size_t			eaten;
	u_int64_t		time;

	data = (t_shared_data *)var;
	eaten = 0;
	pthread_mutex_lock(&data->read);
	info = *data->info;
	fork1 = data->id;
	data->id++;
	fork2 = (fork1 + 1) % info.philo_nr;
	if (data->id == info.philo_nr || (fork1 % 2))
		ft_lock_n_print(data, (fork1 + 1), "%llu %zu is thinking\n");
	pthread_mutex_unlock(&data->read);
	time = ft_time() - (info.last_meal);
	while (1)
	{
		if (time < info.time_to_die && !pthread_mutex_lock(&data->forks[fork1]) && !pthread_mutex_lock(&data->forks[fork2]))
		{
			eaten++;
			if (!ft_lock_n_print(data, (fork1 + 1), "%llu %zu has taken a fork\n") || \
				!ft_lock_n_print(data, (fork1 + 1), "%llu %zu has taken a fork\n") || \
				!ft_lock_n_print(data, (fork1 + 1), "%llu %zu is eating\n"))
				return (pthread_mutex_unlock(&data->forks[fork1]), pthread_mutex_unlock(&data->forks[fork2]), NULL);
			if (!ft_usleep(data, info.time_to_eat))
				return (pthread_mutex_unlock(&data->forks[fork1]), pthread_mutex_unlock(&data->forks[fork2]), NULL);
			pthread_mutex_unlock(&data->forks[fork1]);
			pthread_mutex_unlock(&data->forks[fork2]);
			info.last_meal = ft_time();
			if ((info.to_eat_nr && eaten == info.to_eat_nr))
				return (NULL);
			if (!ft_lock_n_print(data, (fork1 + 1), "%llu %zu is sleeping\n"))
				return (NULL);
			if (!ft_usleep(data, info.time_to_sleep))
				return (NULL);
		}
		if (!ft_lock_n_print(data, (fork1 + 1), "%llu %zu is thinking\n"))
			return (NULL);
		time = ft_time() - (info.last_meal);
		if (time >= info.time_to_die)
		{
			pthread_mutex_lock(&data->read);
			data->died = true;
			pthread_mutex_unlock(&data->read);
			return ("dead");
		}
	}
	return (NULL);
}

static bool	ft_single_philo(t_init *info)
{
	if (info->philo_nr == 1)
	{
		printf("0 1 has taken a fork\n");
		ft_usleep(NULL, info->time_to_die);
		gettimeofday(&info->end, NULL);
		printf("%llu 1 died\n", ft_return_msec(info));
		return (true);
	}
	return (false);
}

bool	ft_create_philos(t_init *info)
{
	pthread_t		*threads;
	t_shared_data	data;
	size_t			i;
	size_t			j;
	size_t			printed;

	i = 0;
	j = 0;
	printed = 0;
	data.info = info;
	data.id = 0;
	data.died = false;
	gettimeofday(&info->start, NULL);
	if (ft_single_philo(info))
		return (true);
	info->last_meal = ft_time();
	threads = malloc((info->philo_nr) * sizeof(pthread_t));
	if (!threads)
		return (printf("threads malloc failed"), false);
	if (!ft_create_mutexes(&data, info->philo_nr))
		return (free(threads), printf("create mutexes failed"), false);
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
		if (info->philo_died && !printed)
		{
			gettimeofday(&info->end, NULL);
			printf("%llu %zu died", ft_return_msec(info), (j + 1));
			printed++;
		}
		j++;
	}
	ft_destroy_mutexes(&data, info->philo_nr);
	free(data.forks);
	free(threads);
	if (i < info->philo_nr)
		return (printf("phtread create failed"), false);
	return (true);
}
