/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asalguer <asalguer@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/17 17:40:43 by asalguer          #+#    #+#             */
/*   Updated: 2025/10/17 17:41:16 by asalguer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	*philo_fork(t_philo *philo)
{
	if (philo->id % 2 == 0)
	{
		pthread_mutex_lock(philo->right_fork);
		safe_print(philo, philo->id, "has taken a fork");
		pthread_mutex_lock(philo->left_fork);
		safe_print(philo, philo->id, "has taken a fork");
	}
	else
	{
		pthread_mutex_lock(philo->left_fork);
		safe_print(philo, philo->id, "has taken a fork");
		pthread_mutex_lock(philo->right_fork);
		safe_print(philo, philo->id, "has taken a fork");
	}
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
	if (philo->rules->n_philo % 2 == 1)
		ft_sleep(philo, 1);
	return (NULL);
}

void	start_routine(t_philo *philo)
{
	if (philo->rules->n_philo > 1 && (philo->id % 2 == 0))
		ft_sleep(philo, philo->rules->time_to_eat / 2);
	while (philo->rules->threads_ready == 1)
	{
		pthread_mutex_lock(&philo->rules->stop_mutex);
		if (philo->rules->stop)
		{
			pthread_mutex_unlock(&philo->rules->stop_mutex);
			break ;
		}
		pthread_mutex_unlock(&philo->rules->stop_mutex);
		philo_fork(philo);
		pthread_mutex_lock(&philo->meal_mutex);
		philo->last_meal = get_time();
		routine_util(philo);
	}
}

void	*routine(void *args)
{
	t_philo	*philo;
	int		ready;

	philo = (t_philo *)args;
	while (1)
	{
		pthread_mutex_lock(&philo->rules->data_mutex);
		ready = philo->rules->threads_ready;
		pthread_mutex_unlock(&philo->rules->data_mutex);
		if (ready)
			break ;
		usleep(50);
	}
	start_routine(philo);
	return (NULL);
}
