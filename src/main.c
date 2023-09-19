/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: cschabra <cschabra@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/09/14 16:02:15 by cschabra      #+#    #+#                 */
/*   Updated: 2023/09/19 18:16:10 by cschabra      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// Rules to think of: 
// - Each philosopher has a number ranging from 1 to 
// number_of_philosophers. Philosopher number 1 sits next to philosopher 
// number number_of_philosophers. Any other philosopher number N sits between
// philosopher number N - 1 and philosopher number N + 1.
//
// - A displayed state message should not be mixed up with another message.
//
// - A message announcing a philosopher died should be displayed no more than
// 10 ms after the actual death of the philosopher. Philos should avoid dying.

// Any state change of a philosopher must be formatted as follows:
//◦ timestamp_in_ms X has taken a fork
//◦ timestamp_in_ms X is eating
//◦ timestamp_in_ms X is sleeping
//◦ timestamp_in_ms X is thinking
//◦ timestamp_in_ms X died

// still need to decide on a maximum input nr. below 1000? or higher?
static bool	ft_check_input(char **argv)
{
	size_t	i;
	size_t	j;

	i = 1;
	j = 0;
	while (argv[i])
	{
		while (argv[i][j])
		{
			if (argv[i][j] < '0' || argv[i][j] > '9' || ft_strlen(argv[i]) > 5)
				return (false);
			j++;
		}
		j = 0;
		i++;
	}
	return (true);
}

void	*ft_grab_fork(void *var)
{
	t_shared_data	*data;
	t_input			input;
	size_t			philo;
	size_t			lastphilo;

	data = (t_shared_data *)var;
	if (pthread_mutex_lock(&data->lock))
		return (printf("mutex lock failed"), NULL);
	input = *data->input;
	philo = data->i;
	lastphilo = input.philo_nr;
	if (philo == lastphilo)
		data->i = 1;
	else
		data->i++;
	if (pthread_mutex_unlock(&data->lock))
		return (printf("mutex lock failed"), NULL);
	if (philo == lastphilo)
	{
		if (pthread_mutex_lock(&data->lock))
			return (printf("mutex lock failed"), NULL);
		if (data->forks[philo] && data->forks[1])
		{
			data->forks[philo] = 0;
			data->forks[1] = 0;
			printf("philo%zu has taken a fork\n", philo);
			printf("philo%zu has taken a fork\n", philo);
			printf("philo%zu is eating\n", philo);
		}
		if (pthread_mutex_unlock(&data->lock))
			return (printf("mutex lock failed"), NULL);
		usleep(input.time_to_eat * 1000);
	}
	else
	{
		if (pthread_mutex_lock(&data->lock))
			return (printf("mutex lock failed"), NULL);
		if (data->forks[philo] && data->forks[philo + 1])
		{
			data->forks[philo] = 0;
			data->forks[philo + 1] = 0;
			printf("philo%zu has taken a fork\n", philo);
			printf("philo%zu has taken a fork\n", philo);
			printf("philo%zu is eating\n", philo);
		}
		if (pthread_mutex_unlock(&data->lock))
			return (printf("mutex lock failed"), NULL);
		usleep(input.time_to_eat * 1000);
	}
	if (pthread_mutex_lock(&data->lock))
		return (printf("mutex lock failed"), NULL);
	printf("philo%zu is sleeping\n", philo);
	if (pthread_mutex_unlock(&data->lock))
		return (printf("mutex lock failed"), NULL);
	usleep(input.time_to_sleep * 1000);
	if (pthread_mutex_lock(&data->lock))
		return (printf("mutex lock failed"), NULL);
	printf("philo%zu is thinking\n", philo);
	if (pthread_mutex_unlock(&data->lock))
		return (printf("mutex lock failed"), NULL);
	return (NULL);
}

int32_t	*ft_create_fork_array(u_int32_t philo_nr)
{
	int32_t	*fork;
	size_t	i;

	i = 0;
	fork = malloc(philo_nr * sizeof(int *));
	if (!fork)
		return (0);
	while (i < philo_nr)
	{
		fork[i] = 1;
		i++;
	}
	return (fork);
}

// when a philo is created, a fork is also spawned. 
bool	ft_create_philos(t_input *input)
{
	pthread_t		*threads;
	t_shared_data	data;
	size_t			i;
	size_t			j;

	i = 0;
	j = 0;
	if (pthread_mutex_init(&data.lock, NULL))
		return (printf("mutex init failed"), false);
	data.forks = ft_create_fork_array(input->philo_nr);
	if (!data.forks)
		return (printf("create fork array failed"), false);
	data.input = input;
	data.i = 1;
	threads = malloc((input->philo_nr) * sizeof(pthread_t));
	if (!threads)
		return (free(data.forks), printf("threads malloc failed"), false);
	while (i < input->philo_nr)
	{
		if (pthread_create(&threads[i], NULL, &ft_grab_fork, (void *)&data))
			break ;
		i++;
	}
	while (j < i)
	{
		if (pthread_join(threads[j], NULL))
			return (free(threads), false);
		j++;
	}
	if (pthread_mutex_destroy(&data.lock))
		return (printf("mutex destroy failed"), false);
	free(data.forks);
	free(threads);
	if (i < input->philo_nr)
		return (printf("phtread create failed"), false);
	return (true);
}

size_t	ft_test_time(void)
{
	struct timeval	start;
	struct timeval	end;

	gettimeofday(&start, NULL);
	usleep(1000000);
	gettimeofday(&end, NULL);
	return ((((end.tv_sec - start.tv_sec) * 1000000) + \
		(end.tv_usec - start.tv_usec)) / 1000);
}

int32_t	main(int32_t argc, char **argv)
{
	t_input		input;
	const char	*str = "Try: ./philo number_of_philosophers time_to_die time_to_eat time_to_sleep \
	\n[Optional: number_of_times_each_philo_must_eat]\nNo negatives :)!\n";

	if (argc < 5 || argc > 6 || !ft_check_input(argv))
	{
		write(STDERR_FILENO, str, ft_strlen(str));
		return (EXIT_FAILURE);
	}
	input.philo_nr = ft_small_atoi(argv[1]);
	if (!input.philo_nr)
		return (EXIT_SUCCESS);
	input.time_to_die = ft_small_atoi(argv[2]);
	input.time_to_eat = ft_small_atoi(argv[3]);
	input.time_to_sleep = ft_small_atoi(argv[4]);
	if (argc == 5)
		input.to_eat_nr = 0;
	else
		input.to_eat_nr = ft_small_atoi(argv[5]);
	if (!ft_create_philos(&input))
		return (EXIT_FAILURE);
	size_t time = ft_test_time();
	printf("milliseconds passed in test_time: %zu\n", time);
	return (EXIT_SUCCESS);
}
