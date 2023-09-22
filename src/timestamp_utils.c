#include "philo.h"

size_t	ft_return_msec(t_input *input)
{
	return ((((input->end.tv_sec - input->start.tv_sec) * 1000000) + \
		(input->end.tv_usec - input->start.tv_usec)) / 1000);
}

// function to check every so often to see if philos died