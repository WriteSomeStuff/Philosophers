/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   philo_active.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: cschabra <cschabra@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/09/26 15:02:00 by cschabra      #+#    #+#                 */
/*   Updated: 2023/10/05 19:25:39 by cschabra      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	ft_copy_data(t_shared_data *data, t_init *info)
{
	info->this_philo = data->id;
	info->philo_nr = data->philo_nr;
	info->time_to_die = data->time_to_die;
	info->time_to_eat = data->time_to_eat;
	info->time_to_sleep = data->time_to_sleep;
	info->max_eat = data->max_eat;
	info->fork1 = info->this_philo;
	info->fork2 = (info->fork1 + 1) % info->philo_nr;
	info->eaten = 0;
	data->id++;
}

static bool	ft_single_philo(t_shared_data *data, t_init *info)
{
	if (data->philo_nr == 1)
	{
		pthread_mutex_lock(&data->forks[0]);
		ft_print(data, info->this_philo + 1, "%ld %zu has taken a fork\n");
		ft_usleep(data, data->time_to_die);
		pthread_mutex_unlock(&data->forks[0]);
		ft_check_if_dead(data);
		return (true);
	}
	return (false);
}

static bool	ft_setup_current_philo(t_shared_data *data, t_init *info)
{
	pthread_mutex_lock(&data->read);
	ft_copy_data(data, info);
	if (ft_single_philo(data, info))
		return (pthread_mutex_unlock(&data->read), false);
	pthread_mutex_unlock(&data->read);
	if (info->this_philo == info->philo_nr - 1 || info->this_philo % 2)
		ft_print(data, info->this_philo + 1, "%ld %zu is thinking\n");
	if (info->this_philo % 2 || \
		(info->philo_nr % 2 && info->this_philo == info->philo_nr - 1))
	{
		if (info->time_to_die < info->time_to_eat)
		{
			if (!ft_usleep(data, info->time_to_die))
				return (false);
		}
		else
		{
			if (!ft_usleep(data, info->time_to_eat))
				return (false);
		}
	}
	return (true);
}

void	*ft_philo_loop(void *var)
{
	t_shared_data	*data;
	t_init			info;

	data = (t_shared_data *)var;
	if (!ft_setup_current_philo(data, &info))
		return (NULL);
	while (!ft_check_if_dead(data))
	{
		if (!ft_eating(data, &info, info.fork1, info.fork2))
			break ;
		if (!ft_sleeping(data, &info, info.fork1) || \
			!ft_thinking(data, info.fork1))
			break ;
	}
	return (NULL);
}
