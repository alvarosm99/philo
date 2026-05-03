/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_functions.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asalguer <asalguer@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/17 17:52:12 by asalguer          #+#    #+#             */
/*   Updated: 2025/10/17 17:55:21 by asalguer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int	ft_atoi(char *str)
{
	int	i;
	int	sign;
	int	n;

	i = 0;
	n = 0;
	sign = 1;
	while (str[i] != '\0')
	{
		if (str[i] < '0' || str[i] > '9')
			return (-1);
		i++;
	}
	i = 0;
	while (str[i] >= '0' && str[i] <= '9')
	{
		n = n * 10 + (str[i] - '0');
		i++;
	}
	return (n * sign);
}

long	get_time(void)
{
	struct timeval	current_time;
	long			time;

	gettimeofday(&current_time, NULL);
	time = current_time.tv_sec * 1000 + current_time.tv_usec / 1000;
	return (time);
}

void	ft_sleep(t_philo *philo, int ms)
{
	long	end;
	long	now;

	end = get_time() + ms;
	while (1)
	{
		now = get_time();
		if (now >= end)
			break ;
		pthread_mutex_lock(&philo->rules->stop_mutex);
		if (philo->rules->stop)
		{
			pthread_mutex_unlock(&philo->rules->stop_mutex);
			break ;
		}
		pthread_mutex_unlock(&philo->rules->stop_mutex);
	}
}

void	clean_all(t_rules *rules)
{
	int	i;

	pthread_mutex_destroy(&rules->print_mutex);
	pthread_mutex_destroy(&rules->stop_mutex);
	pthread_mutex_destroy(&rules->data_mutex);
	i = 0;
	while (i < rules->n_philo)
	{
		pthread_mutex_destroy(&rules->philo[i].philo_mutex);
		pthread_mutex_destroy(&rules->philo[i].meal_mutex);
		pthread_mutex_destroy(&rules->forks[i]);
		i++;
	}
	free(rules->philo);
	free(rules->forks);
	free(rules);
}
