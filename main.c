#include "philo_one.h"

void *check_died(void *tmp_philo)
{
	t_thread *philo = (t_thread *)tmp_philo;
	while (!error)
	{
//		if (philo->eat == 1)
//		{
//			philo->init = get_current_time();
//			philo->eat = 0;
//		}
		if (get_current_time() - philo->init > input_philo_array[TIME_TO_DIE])
		{
			ft_str_print("died\n", philo);
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
//	int i = 0;
	t_thread *philo = (t_thread *)data;
	pthread_create(&died, NULL, check_died, (void *)philo);
	philo->init = get_current_time();
	while (!error)
	{
		pthread_mutex_lock(&philo->left_fork);
		ft_str_print("has taken a fork\n", philo);
		pthread_mutex_lock(&philo->right_fork);
		ft_str_print("has taken a fork\n", philo);
//		philo->eat = 1;
		philo->init = get_current_time();
		ft_str_print("is eating\n", philo);
		usleep(input_philo_array[TIME_TO_EAT] * 1000);
		pthread_mutex_unlock(&philo->left_fork);
		pthread_mutex_unlock(&philo->right_fork);
		ft_str_print("is sleeping\n", philo);
		usleep(input_philo_array[TIME_TO_SLEEP] * 1000);
		ft_str_print("is thinking\n", philo);
	}
	return NULL;
}


void thread_func()
{
	pthread_mutex_t mutex[input_philo_array[NUMBER_OF_PHILOSOPHERS]];
	t_thread data[input_philo_array[NUMBER_OF_PHILOSOPHERS]];
	size_t i = 0;
	pthread_t thread[input_philo_array[NUMBER_OF_PHILOSOPHERS]];

	while (i < input_philo_array[NUMBER_OF_PHILOSOPHERS])
	{
		pthread_mutex_init(&mutex[i], NULL);
		i++;
	}
	i = 0;
	g_time = get_current_time();
	while (i < input_philo_array[NUMBER_OF_PHILOSOPHERS])
	{
		data[i].id = i;
		data[i].right_fork = mutex[i % input_philo_array[NUMBER_OF_PHILOSOPHERS]];
		data[i].left_fork = mutex[i - 1 % input_philo_array[NUMBER_OF_PHILOSOPHERS]];
		i++;
	}
	i = 0;
	while (i < input_philo_array[NUMBER_OF_PHILOSOPHERS])
	{
		pthread_create(&thread[i], NULL, philo, (void *)&data[i]);
		i += 2;
	}
	i = 1;
	while (i < input_philo_array[NUMBER_OF_PHILOSOPHERS])
	{
		pthread_create(&thread[i], NULL, philo, (void *)&data[i]);
		i += 2;
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
		input_philo_array = (int *)ft_x_malloc(sizeof(int) * 4);
		while (++i < 4)
			input_philo_array[i] = ft_atoi(argv[i + 1]);
//		check_count_of_eat = 0;
	}
    else
	{
		input_philo_array = (int *)ft_x_malloc(sizeof(int) * 5);
		while (++i < 5)
			input_philo_array[i] = ft_atoi(argv[i + 1]);
//		check_count_of_eat = 1;
	}
	thread_func();
	return (0);
}
