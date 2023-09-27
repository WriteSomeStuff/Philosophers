/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: cschabra <cschabra@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/09/14 16:02:15 by cschabra      #+#    #+#                 */
/*   Updated: 2023/09/26 17:57:58 by cschabra      ########   odam.nl         */
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

void	leaks(void)
{
	system("leaks -q philo");
}

int32_t	main(int32_t argc, char **argv)
{
	t_init	info;

	// atexit(leaks);
	if (argc < 5 || argc > 6 || !ft_check_input(argv))
	{
		write(STDERR_FILENO, WRONGINPUT, ft_strlen(WRONGINPUT));
		return (EXIT_FAILURE);
	}
	info.philo_nr = ft_small_atoi(argv[1]);
	if (info.philo_nr > 499)
		return (printf("don't you think that's a lot..?"), EXIT_FAILURE);
	info.time_to_die = ft_small_atoi(argv[2]);
	info.time_to_eat = ft_small_atoi(argv[3]);
	info.time_to_sleep = ft_small_atoi(argv[4]);
	if (!info.philo_nr || !info.time_to_die || !info.time_to_eat || !info.time_to_sleep)
		return (printf("gib higher than 0 plz"), EXIT_FAILURE);
	if (argc == 5)
		info.max_eat = 0;
	else
		info.max_eat = ft_small_atoi(argv[5]);
	info.eaten = 0;
	if (!ft_prep_threads(&info))
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
