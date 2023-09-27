/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   string_utils.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: cschabra <cschabra@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/09/18 15:57:16 by cschabra      #+#    #+#                 */
/*   Updated: 2023/09/18 16:05:49 by cschabra      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

bool	ft_int_array(t_shared_data *data, t_init *info)
{
	size_t	i;

	i = 0;
	data->forks_available = malloc(info->philo_nr * sizeof(int32_t *));
	if (!data->forks_available)
		return (false);
	while (i < info->philo_nr)
	{
		data->forks_available[i] = 1;
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
