#include "../include/philo.h"

static void	set_initial_time(t_rules *rules)
{
	int i;

	rules->start_time = get_time();
	i = 0;
	while (i < rules->n_philo)
	{
		pthread_mutex_lock(&rules->philo[i].meal_mutex);
		rules->philo[i].last_meal = rules->start_time;
		rules->philo[i].eating = 0;
		pthread_mutex_unlock(&rules->philo[i].meal_mutex);
		i++;
	}
}

void	*one_philo_routine(t_philo *philo)
{
	if (philo->rules->n_philo == 1)
	{
		philo->rules->start_time = get_time();
		pthread_mutex_lock(philo->left_fork);
		safe_print(philo, philo->id, "has taken a fork");
		ft_sleep(philo, philo->rules->time_to_die);
		safe_print(philo, philo->id, "has died");
		pthread_mutex_lock(&philo->rules->stop_mutex);
		philo->rules->stop = 1;
		pthread_mutex_unlock(&philo->rules->stop_mutex);
		pthread_mutex_unlock(philo->left_fork);
		return (NULL);
	}
	return (NULL);
}

void	init_routine(t_rules *rules)
{
	int i;

	one_philo_routine(&rules->philo[0]);
	if (rules->stop == 1)
		return ;
	i = 0;
	while (i < rules->n_philo)
	{
		pthread_create(&rules->philo[i].thrd, NULL, &routine, &rules->philo[i]);
		i++;
	}
	set_initial_time(rules);
	pthread_create(&rules->monitor, NULL, &death_checker, rules->philo);
	pthread_mutex_lock(&rules->data_mutex);
	rules->threads_ready = 1;
	pthread_mutex_unlock(&rules->data_mutex);
	i = 0;
	while (i < rules->n_philo)
		pthread_join(rules->philo[i++].thrd, NULL);
	pthread_join(rules->monitor, NULL);
}

void	*death_checker_utils(t_philo *philo, t_rules *rules, long *last_meal, long *current)
{
	int	i;

	i = 0;
	while (i < rules->n_philo)
	{
		pthread_mutex_lock(&philo[i].meal_mutex);
		*last_meal = philo[i].last_meal;
		pthread_mutex_unlock(&philo[i].meal_mutex);
		*current = get_time();
		if ((*current - *last_meal) > rules->time_to_die)
		{
			pthread_mutex_lock(&rules->stop_mutex);
			if (!rules->stop)
			{
				pthread_mutex_lock(&rules->print_mutex);
				printf("%ld %i died\n", *current - rules->start_time, philo[i].id);
				pthread_mutex_unlock(&rules->print_mutex);
				rules->stop = 1;
			}
			pthread_mutex_unlock(&rules->stop_mutex);
			return ((void *)1);
		}
		i++;
	}
	return (NULL);
}

void	*death_checker(void *args)
{
	long    last_meal;
	long    current;
	t_philo *philo;
	t_rules *rules;

	philo = (t_philo *)args;
	rules = philo[0].rules;
	while (1)
	{
		pthread_mutex_lock(&rules->stop_mutex);
		if (rules->stop)
		{
			pthread_mutex_unlock(&rules->stop_mutex);
			return (NULL);
		}
		pthread_mutex_unlock(&rules->stop_mutex);
		if (death_checker_utils(philo, rules, &last_meal, &current))
			return (NULL);
		usleep(50);
	}
	return (NULL);
}