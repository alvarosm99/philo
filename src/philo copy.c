#include "../include/philo.h"

void	*philo_fork(t_philo *philo)
{
	pthread_mutex_t	*first;
	pthread_mutex_t	*second;

	if (philo->left_fork < philo->right_fork)
	{
		first = philo->left_fork;
		second = philo->right_fork;
	}
	else
	{
		first = philo->right_fork;
		second = philo->left_fork;
	}
	pthread_mutex_lock(first);
	safe_print(philo, philo->id, "has taken a fork");
	pthread_mutex_lock(second);
	safe_print(philo, philo->id, "has taken a fork");
	return (NULL);
}

void	*drop_fork(t_philo *philo)
{
	if (philo->id % 2 == 0)
	{
		pthread_mutex_unlock(philo->left_fork);
		pthread_mutex_unlock(philo->right_fork);
	}
	else
	{
		pthread_mutex_unlock(philo->right_fork);
		pthread_mutex_unlock(philo->left_fork);
	}
	return (NULL);
}

void	*routine_util(t_philo *philo)
{
	pthread_mutex_unlock(&philo->meal_mutex);
	safe_print(philo, philo->id, "is eating");
	ft_sleep(philo, philo->rules->time_to_eat);
	drop_fork(philo);
	safe_print(philo, philo->id, "is sleeping");
	ft_sleep(philo, philo->rules->time_to_sleep);
	safe_print(philo, philo->id, "is thinking");
	return (NULL);
}

void	*routine(void *args)
{
	t_philo *philo;

	philo = (t_philo *)args;
	if (philo->rules->threads_ready == 1)
	{
		while (philo->rules->threads_ready == 1)
		{
			pthread_mutex_lock(&philo->rules->stop_mutex);
			if (philo->rules->stop)
			{
				pthread_mutex_unlock(&philo->rules->stop_mutex);
				break;
			}
			pthread_mutex_unlock(&philo->rules->stop_mutex);
			philo_fork(philo);
			pthread_mutex_lock(&philo->meal_mutex);
			philo->last_meal = get_time();
			routine_util(philo);
			if (philo->rules->n_philo > 2 && philo->id % 2)
				usleep(200);
		}
	}
	return (NULL);
}
