#include "philo.h"

static void	ft_lock_n_print(t_shared_data *data, size_t philo, char *str)
{
	t_input	*input;

	pthread_mutex_lock(&data->write);
	input = data->input;
	gettimeofday(&input->end, NULL);
	printf(str, ft_return_msec(input), philo);
	pthread_mutex_unlock(&data->write);
}

static void	*ft_philo_loop(void *var)
{
	t_shared_data	*data;
	t_input			input;
	size_t			fork1;
	size_t			fork2;
	size_t			eaten;
	bool			dead;

	data = (t_shared_data *)var;
	eaten = 0;
	dead = false;
	pthread_mutex_lock(&data->read);
	input = *data->input;
	fork1 = data->id - 1;
	data->id++;
	pthread_mutex_unlock(&data->read);
	fork2 = (fork1 + 1) % input.philo_nr;
	while (1)
	{
		if (fork1 % 2 && eaten == 0)
			ft_lock_n_print(data, fork1, "%zu %zu is thinking\n");
		if (!pthread_mutex_lock(&data->forks[fork1]) && !pthread_mutex_lock(&data->forks[fork2]))
		{
			eaten++;
			ft_lock_n_print(data, fork1, "%zu %zu has taken a fork\n");
			ft_lock_n_print(data, fork1, "%zu %zu has taken a fork\n");
			ft_lock_n_print(data, fork1, "%zu %zu is eating\n");
			usleep(input.time_to_eat * 1000);
			pthread_mutex_unlock(&data->forks[fork1]);
			pthread_mutex_unlock(&data->forks[fork2]);
		}
		if ((input.to_eat_nr && eaten == input.to_eat_nr) || dead == true)
			return (NULL);
		ft_lock_n_print(data, fork1, "%zu %zu is sleeping\n");
		usleep(input.time_to_sleep * 1000);
		ft_lock_n_print(data, fork1, "%zu %zu is thinking\n");
	}
	return (NULL);
}

bool	ft_create_philos(t_input *input)
{
	pthread_t		*threads;
	t_shared_data	data;
	size_t			i;
	size_t			j;

	i = 0;
	j = 0;
	data.input = input;
	data.id = 1;
	threads = malloc((input->philo_nr) * sizeof(pthread_t));
	if (!threads)
		return (printf("threads malloc failed"), false);
	if (!ft_create_mutexes(&data, input->philo_nr))
		return (free(threads), printf("create mutexes failed"), false);
	gettimeofday(&input->start, NULL);
	while (i < input->philo_nr)
	{
		if (pthread_create(&threads[i], NULL, &ft_philo_loop, (void *)&data))
			break ;
		i++;
	}
	while (j < i)
	{
		if (pthread_join(threads[j], NULL))
		{
			ft_destroy_mutexes(&data, input->philo_nr);
			free(data.forks);
			free(threads);
			return (false);
		}
		j++;
	}
	ft_destroy_mutexes(&data, input->philo_nr);
	free(data.forks);
	free(threads);
	if (i < input->philo_nr)
		return (printf("phtread create failed"), false);
	return (true);
}
