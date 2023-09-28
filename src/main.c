/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: cschabra <cschabra@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/09/14 16:02:15 by cschabra      #+#    #+#                 */
/*   Updated: 2023/09/28 19:13:08 by cschabra      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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
			if (ft_strlen(argv[i]) > 5)
				return (false);
			if (argv[i][j] < '0' || argv[i][j] > '9')
				return (false);
			j++;
		}
		j = 0;
		i++;
	}
	return (true);
}

int32_t	main(int32_t argc, char **argv)
{
	t_shared_data	data;

	if (argc < 5 || argc > 6 || !ft_check_input(argv))
	{
		write(STDERR_FILENO, WRONGINPUT, ft_strlen(WRONGINPUT));
		return (EXIT_FAILURE);
	}
	data.philo_nr = ft_small_atoi(argv[1]);
	if (!data.philo_nr || data.philo_nr > 499)
		return (printf("above 0 and below 500 :)"), EXIT_FAILURE);
	data.time_to_die = ft_small_atoi(argv[2]);
	data.time_to_eat = ft_small_atoi(argv[3]);
	data.time_to_sleep = ft_small_atoi(argv[4]);
	if (!data.time_to_die || !data.time_to_eat || !data.time_to_sleep)
		return (printf("gib higher than 0 plz"), EXIT_FAILURE);
	if (argc == 5)
		data.max_eat = 0;
	else
		data.max_eat = ft_small_atoi(argv[5]);
	if (!ft_prep_threads(&data))
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
