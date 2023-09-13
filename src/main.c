#include "philo.h"

void	*ft_funct(void *var)
{
	int	i = *(int *)var;
	printf("%i\n", i);
	return (NULL);
}

int	main(void)
{
	pthread_t	thread1;
	pthread_t	thread2;
	int			i;

	i = 1;
	if (pthread_create(&thread1, NULL, &ft_funct, (void *)&i))
		return (1);
	if (pthread_create(&thread2, NULL, &ft_funct, (void *)&i))
		return (1);
	if (pthread_join(thread1, NULL))
		return (1);
	if (pthread_join(thread2, NULL))
		return (1);
}
