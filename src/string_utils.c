/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   string_utils.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: cschabra <cschabra@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/09/18 15:57:16 by cschabra      #+#    #+#                 */
/*   Updated: 2023/09/28 18:08:30 by cschabra      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

bool	ft_int_array(t_shared_data *data)
{
	size_t	i;

	i = 0;
	data->done_eating = malloc(data->philo_nr * sizeof(int32_t *));
	if (!data->done_eating)
		return (false);
	while (i < data->philo_nr)
	{
		data->done_eating[i] = 0;
		i++;
	}
	return (true);
}

u_int32_t	ft_small_atoi(char *str)
{
	size_t		i;
	u_int32_t	res;

	i = 0;
	res = 0;
	while (str[i])
	{
		res = res * 10 + (str[i] - '0');
		i++;
	}
	return (res);
}

size_t	ft_strlen(const char *str)
{
	size_t	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}
