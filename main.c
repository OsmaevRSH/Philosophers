#include "philo_one.h"
#include "stdio.h"

int		main(int argc, char **argv)
{
	int	*input_philo_array;
	int i;

	int a = 0;
	i = -1;
    if (argc > 6 || argc < 5)
	{
    	write(2, "Error: invalid count of arguments\n", 34);
		return (1);
	}
    else if (argc == 5)
	{
		input_philo_array = (int *)ft_x_malloc(sizeof(int) * 4);
		while (++i < 4)
			input_philo_array[i] = ft_atoi(argv[i + 1]);
		a = 1;
	}
    else
	{
		input_philo_array = (int *)ft_x_malloc(sizeof(int) * 5);
		while (++i < 5)
			input_philo_array[i] = ft_atoi(argv[i + 1]);
	}
	i = -1;
	while (++i < 5 - a)
	{
		printf("%d\n", input_philo_array[i]);
	}
	return (0);
}
