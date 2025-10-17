#include "../include/philo.h"

int	main (int argc, char** argv)
{
	t_rules		*rules;

	if (args_check(argc, argv) != 0)
		return (1);
	rules = smalloc(sizeof(t_rules));
	if (!rules)
		return (2);
	init_data(argv, rules);
	init_routine(rules);
	clean_all(rules);
	return 0;
}

