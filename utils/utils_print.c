/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_print.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asalguer <asalguer@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/17 17:55:07 by asalguer          #+#    #+#             */
/*   Updated: 2025/10/17 17:55:08 by asalguer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	safe_print(t_philo *philo, int id, const char *msg)
{
	long	ts;

	pthread_mutex_lock(&philo->rules->print_mutex);
	if (!philo->rules->stop)
	{
		ts = get_time() - philo->rules->start_time;
		printf("%ld %d %s\n", ts, id, msg);
	}
	pthread_mutex_unlock(&philo->rules->print_mutex);
}
