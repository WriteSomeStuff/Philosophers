/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: cschabra <cschabra@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/09/14 16:02:15 by cschabra      #+#    #+#                 */
/*   Updated: 2023/09/18 18:44:47 by cschabra      ########   odam.nl         */
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

void	*ft_funct(void *var)
{
	long	*id;

	id = (long *)var;
	printf("philo id: %ld\n", *id);
	return (NULL);
}

// when a philo is created, a fork is also spawned. 
bool	ft_create_philos(t_input *input)
{
	pthread_t		*threads;
	t_shared_data	data;
	size_t			i;

	i = 0;
	data.forks = input->philo_nr;
	threads = malloc((input->philo_nr) * sizeof(pthread_t));
	if (!threads)
		return (false);
	while (i < input->philo_nr)
	{
		if (pthread_create(&threads[i], NULL, &ft_funct, (void *)&threads[i]))
			return (free(threads), false);
		i++;
	}
	i = 0;
	while (i < input->philo_nr)
	{
		if (pthread_join(threads[i], NULL))
			return (free(threads), false);
		i++;
	}
	free(threads);
	return (true);
}

int32_t	ft_test_time(void)
{
	struct timeval	start;
	struct timeval	end;
	int32_t			i;

	gettimeofday(&start, NULL);
	i = 0;
	sleep(1);
	gettimeofday(&end, NULL);
	return ((((end.tv_sec - start.tv_sec) * 1000000) + \
		(end.tv_usec - start.tv_usec)) / 1000);
}

int32_t	main(int32_t argc, char **argv)
{
	t_input			input;
	const char		*str = "Try: ./philo number_of_philosophers time_to_die time_to_eat time_to_sleep \
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
	ft_test_time();
	int32_t time = ft_test_time();
	printf("milliseconds passed in test_time: %i\n", time);
	return (EXIT_SUCCESS);
}
