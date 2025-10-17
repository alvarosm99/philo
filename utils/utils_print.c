#include "../include/philo.h"

void	safe_print(t_philo *philo, int id, const char *msg)
{
	long ts;
	pthread_mutex_lock(&philo->rules->print_mutex);
	if (!philo->rules->stop)
	{
		ts = get_time() - philo->rules->start_time;
		printf("%ld %d %s\n", ts, id, msg);
	}
	pthread_mutex_unlock(&philo->rules->print_mutex);
}
