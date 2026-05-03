/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asalguer <asalguer@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/17 17:51:30 by asalguer          #+#    #+#             */
/*   Updated: 2025/10/17 17:51:31 by asalguer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int	main(int argc, char **argv)
{
	t_rules	*rules;

	if (args_check(argc, argv) != 0)
		return (1);
	rules = smalloc(sizeof(t_rules));
	if (!rules)
		return (2);
	init_data(argv, rules);
	init_routine(rules);
	clean_all(rules);
	return (0);
}
