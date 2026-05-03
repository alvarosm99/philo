/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asalguer <asalguer@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/17 17:50:57 by asalguer          #+#    #+#             */
/*   Updated: 2025/10/17 17:51:16 by asalguer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int	args_check(int argc, char **argv)
{
	if (argc != 5)
	{
		instructions();
		return (1);
	}
	if (ft_atoi(argv[1]) < 0 || ft_atoi(argv[2]) < 0 || ft_atoi(argv[3]) < 0
		|| ft_atoi(argv[4]) < 0)
	{
		printf("Error: Arguments must be possitive numbers.\n");
		return (2);
	}
	else
		return (0);
}

void	*smalloc(size_t bytes)
{
	void	*memory;

	memory = malloc(bytes);
	if (memory == NULL)
		printf("Error: malloc couldn't allocate enough memory\n");
	return (memory);
}

t_philo	*init_philo(t_rules *rules)
{
	t_philo	*philo;
	int		i;

	philo = smalloc(sizeof(t_philo) * rules->n_philo);
	if (!philo)
		return (NULL);
	i = 0;
	while (i < rules->n_philo)
	{
		memset(&philo[i], 0, sizeof(t_philo));
		philo[i].id = i + 1;
		pthread_mutex_init(&philo[i].philo_mutex, NULL);
		pthread_mutex_init(&philo[i].meal_mutex, NULL);
		philo[i].rules = rules;
		philo[i].left_fork = &rules->forks[i];
		philo[i].right_fork = &rules->forks[(i + 1) % rules->n_philo];
		i++;
	}
	return (philo);
}

void	*init_data(char **argv, t_rules *rules)
{
	int	i;

	memset(rules, 0, sizeof(*rules));
	rules->n_philo = ft_atoi(argv[1]);
	rules->time_to_die = ft_atoi(argv[2]);
	rules->time_to_eat = ft_atoi(argv[3]);
	rules->time_to_sleep = ft_atoi(argv[4]);
	rules->stop = 0;
	rules->start_time = get_time();
	rules->forks = smalloc(sizeof(pthread_mutex_t) * rules->n_philo);
	if (!rules->forks)
		return (NULL);
	i = 0;
	while (i < rules->n_philo)
		pthread_mutex_init(&rules->forks[i++], NULL);
	pthread_mutex_init(&rules->print_mutex, NULL);
	pthread_mutex_init(&rules->stop_mutex, NULL);
	pthread_mutex_init(&rules->data_mutex, NULL);
	rules->philo = init_philo(rules);
	return (NULL);
}
