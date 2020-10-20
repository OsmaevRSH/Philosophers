#include "philo_one.h"

void	*ft_x_malloc(size_t size)
{
	void	*ptr;

	if (!(ptr = malloc(size)))
	{
		write(2, "Error: malloc error\n", 20);
		exit(1);
	}
	return (ptr);
}

