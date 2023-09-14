/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: cschabra <cschabra@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/09/14 16:02:15 by cschabra      #+#    #+#                 */
/*   Updated: 2023/09/14 18:13:19 by cschabra      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*ft_funct(void *var)
{
	int32_t	i;

	i = *(int32_t *)var;
	printf("%i\n", i);
	return (NULL);
}

int32_t	ft_atoi(char *str)
{
	str = NULL;
	return (1);
}

size_t	ft_strlen(const char *str)
{
	size_t	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

int32_t	main(int32_t argc, char **argv)
{
	pthread_t	*threads;
	int32_t		i;
	const char	*str = "try: ./philo number_of_philosophers time_to_die time_to_eat time_to_sleep \
	\n[optional: number_of_times_each_philosopher_must_eat]\n";

	if (argc < 2)
	{
		write(STDERR_FILENO, str, ft_strlen(str));
		return (EXIT_FAILURE);
	}
	i = ft_atoi(argv[1]);
	printf("%i\n", i);
	threads = malloc((i + 1) * sizeof(pthread_t));
	if (!threads)
		return (EXIT_FAILURE);
	// if (pthread_create(&threads, NULL, &ft_funct, (void *)&i))
	// 	return (EXIT_FAILURE);
	// if (pthread_join(threads, NULL))
	// 	return (EXIT_FAILURE);
	free(threads);
	return (EXIT_SUCCESS);
}
