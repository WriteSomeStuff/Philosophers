/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   philo_active.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: cschabra <cschabra@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/09/26 15:02:00 by cschabra      #+#    #+#                 */
/*   Updated: 2023/09/26 17:03:38 by cschabra      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	ft_setup_current_philo(t_shared_data *data, t_init *info)
{
	pthread_mutex_lock(&data->read);
	*info = *data->info;
	info->this_philo = data->id;
	data->id++;
	pthread_mutex_unlock(&data->read);
	info->fork1 = info->this_philo;
	info->fork2 = (info->fork1 + 1) % info->philo_nr;
	if (info->this_philo == info->philo_nr - 1 || info->this_philo % 2)
		ft_lock_n_print(data, info->this_philo + 1, "%lld %zu is thinking\n");
	if (info->this_philo % 2 || \
		(info->philo_nr % 2 && info->this_philo == info->philo_nr - 1))
		ft_usleep(data, info->time_to_eat);
}

void	*ft_philo_loop(void *var)
{
	t_shared_data	*data;
	t_init			info;

	data = (t_shared_data *)var;
	ft_setup_current_philo(data, &info);
	while (1)
	{
		if (ft_check_starvation(data, &info))
			return ("starved");
		if (!ft_eating(data, &info, info.fork1, info.fork2))
			break ;
		if ((info.max_eat && info.eaten == info.max_eat) || \
			!ft_sleeping(data, &info, info.fork1) || \
			!ft_thinking(data, info.fork1))
			break ;
	}
	return (NULL);
}

bool	ft_single_philo(t_init *info)
{
	if (info->philo_nr == 1)
	{
		printf("0 1 has taken a fork\n");
		usleep(info->time_to_die * 1000);
		gettimeofday(&info->end, NULL);
		printf("%lld 1 died\n", ft_return_msec(info));
		return (true);
	}
	return (false);
}
