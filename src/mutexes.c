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

}

bool	ft_create_mutexes(t_shared_data *data, u_int32_t amount)
{
	size_t	i;

	i = 0;
	if (pthread_mutex_init(&data->write, NULL))
		return (false);
	if (pthread_mutex_init(&data->read, NULL))
		return (pthread_mutex_destroy(&data->write), false);
	data->forks = malloc(amount * sizeof(pthread_mutex_t *));
	if (!data->forks)
		return (ft_destroy_mutexes(data, i), false);
	while (i < amount)
	{
		if (pthread_mutex_init(&data->forks[i], NULL))
		{
			ft_destroy_mutexes(data, i);
			free(data->forks);
			return (false);
		}
		i++;
	}
	return (true);
}
