#include "philo.h"

u_int64_t	ft_time(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return (((time.tv_sec) * 1000) + ((time.tv_usec) / 1000));
}

bool	ft_usleep(t_shared_data *data, u_int32_t ms)
{
	u_int64_t	start;

	start = ft_time();
	while ((ft_time() - start) < ms)
	{
		if(ft_check_if_dead(data))
			return (false);
		usleep(200);
	}
	return (true);
}

u_int64_t	ft_return_msec(t_init *info)
{
	return ((((info->end.tv_sec - info->start.tv_sec) * 1000000) + \
		(info->end.tv_usec - info->start.tv_usec)) / 1000);
}
