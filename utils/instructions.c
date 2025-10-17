#include "../include/philo.h"

void	instructions(void)
{
	write(1, " _____ _       _        \n", 26);
	write(1, "| ___ | |   (_) |       \n", 26);
	write(1, "| |_/ / |__  _| |  ___  \n", 26);
	write(1, "|  __/|  _ || | |/  _ | \n", 26);
	write(1, "| |   | | | | | |  (_)| \n", 26);
	write(1, "|_|   |_| |_|_|_|| ___/\n\n", 26);
	write(1, "-------------           \n", 26);
	write(1, "Instructions:           \n", 26);
	write(1, "-------------           \n\n", 27);
	write(1, "./philo [arg1] [arg2] [arg3] [arg4]\n", 37);
	write(1, "arg1: Number of philosophers\n", 30);
	write(1, "arg2: Time to die\n", 19);
	write(1, "arg3: Time to eat\n", 19);
	write(1, "arg4: Time to sleep\n\n", 22);
}
