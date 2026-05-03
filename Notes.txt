#include "philo.h"

void	*print_somethint(void)
{
	printf("Something\n");
}

int	main(int argc, char** argv)
{
	pthread_t t1; //Stores metadata needed by the kernel to manage threads
	
	//Create a thread:
	pthread_create(&t1, NULL, &print_somethint, NULL); /*
	&t1 (thread) -> pointer to the target thread (output)
	NULL (attr) -> thread attributes, NULL = default
	print_something (start_routine) -> function that you want the thread to do, must have void* ()(void)
	NULL (arg) -> argument/s for start_routine, NULL = no atributes needed, to pass multiple values pass a pointer to a struct
	
	Returns:
	- 0 on success
	- EAGAIN for resource exhaustion
	- EINVAL for bad attributes
	- EPERM for insufficient permissions
	*/
	
	//Wait until the thread finishes its execution:
	pthread_join(t1, NULL); /*
	t1 (thread) -> the thread ID to wait for
	NULL (retval) -> 

	Returns:
	- 0 on success
	- ESRCH the thread wasn't found
	- EINVAL the thread is not joinable or another join is in process for this thread
	- EDEADLK: Deadlock
	*/
	
	
	
	
	
	
	
	
	return 0;
}