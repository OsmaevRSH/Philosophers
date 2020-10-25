#include "philo_one.h"

void *check_died(void *tmp_philo)
{
	t_thread *philo = (t_thread *)tmp_philo;
	while (!error)
	{
		if (get_current_time() - philo->init > input_philo_array[TIME_TO_DIE])
		{
			ft_str_print(4, philo);
			error = 1;
			pthread_mutex_unlock(&philo->right_fork);
			pthread_mutex_unlock(&philo->left_fork);
		}
	}
	return (NULL);
}

void	*philo(void *data)
{
	pthread_t died;
	unsigned eat = input_philo_array[TIME_TO_EAT] * 1000;
	unsigned sleep = input_philo_array[TIME_TO_SLEEP] * 1000;
	t_thread *philo = (t_thread *)data;
	if (philo->id & 1)
		usleep(input_philo_array[TIME_TO_EAT] * 1000);
	pthread_create(&died, NULL, check_died, (void *)philo);
	philo->init = get_current_time();
	while (!error)
	{
		pthread_mutex_lock(&philo->left_fork);
		ft_str_print(0, philo);
		pthread_mutex_lock(&philo->right_fork);
		ft_str_print(0, philo);
		philo->init = get_current_time();
		ft_str_print(1, philo);
		usleep(eat);
		pthread_mutex_unlock(&philo->left_fork);
		pthread_mutex_unlock(&philo->right_fork);
		ft_str_print(2, philo);
		usleep(sleep);
		ft_str_print(3, philo);
	}
	return NULL;
}

void thread_func()
{
	pthread_mutex_t mutex[input_philo_array[NUMBER_OF_PHILOSOPHERS]];
	t_thread data[input_philo_array[NUMBER_OF_PHILOSOPHERS]];
	pthread_t thread[input_philo_array[NUMBER_OF_PHILOSOPHERS]];
	uint8_t i = 0;

	while (i < input_philo_array[NUMBER_OF_PHILOSOPHERS])
	{
		pthread_mutex_init(&mutex[i], NULL);
		i++;
	}
	i = 0;
	while (i < input_philo_array[NUMBER_OF_PHILOSOPHERS])
	{
		data[i].id = i;
		data[i].right_fork = mutex[i % input_philo_array[NUMBER_OF_PHILOSOPHERS]];
		data[i].left_fork = mutex[(i - 1) % input_philo_array[NUMBER_OF_PHILOSOPHERS]];
		i++;
	}
	i = 0;
	g_time = get_current_time();
	while (i < input_philo_array[NUMBER_OF_PHILOSOPHERS])
	{
		pthread_create(&thread[i], NULL, philo, (void *)&data[i]);
		i++;
	}
	while (!error)
	{
		;
	}
	i = 0;
	while (i < input_philo_array[NUMBER_OF_PHILOSOPHERS])
	{
		pthread_mutex_destroy(&mutex[i]);
		i++;
	}
	write(2, "error\n", 6);
}

int		main(int argc, char **argv)
{
	int i;

	i = -1;
    if (argc > 6 || argc < 5)
	{
    	write(2, "Error: invalid count of arguments\n", 34);
		return (1);
	}
    if (argc == 5)
	{
		input_philo_array = (int *)malloc(sizeof(int) * 4);
		while (++i < 4)
			input_philo_array[i] = ft_atoi(argv[i + 1]);
	}
    else
	{
		input_philo_array = (int *)malloc(sizeof(int) * 5);
		while (++i < 5)
			input_philo_array[i] = ft_atoi(argv[i + 1]);
	}
	thread_func();
	return (0);
}
