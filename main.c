#include "philo_one.h"

void	*philo(void *data)
{
//	pthread_t died;
	t_thread *philo = (t_thread *)data;
	philo->init = get_current_time();
//	pthread_create(&died, NULL, check_died, (void *)&philo->init);
//	pthread_detach(died);
	while (!error)
	{
//		pthread_mutex_lock(&philo->left_philo);
		pthread_mutex_lock(&philo->right_philo);
		pthread_mutex_lock(&philo->philo);
		pthread_mutex_lock(&philo->left_fork);
		ft_str_print(" has taken a fork\n", philo);
		pthread_mutex_lock(&philo->right_fork);
		ft_str_print(" has taken a fork\n", philo);
		ft_str_print(" is eating\n", philo);
		philo->init = get_current_time();
		usleep(input_philo_array[2] * 1000);
		if (get_current_time() - philo->init > input_philo_array[1])
		{
			printf("%ld %zu died\n", get_current_time() - g_time, philo->id);
			error = 1;
			pthread_mutex_unlock(&philo->right_fork);
			pthread_mutex_unlock(&philo->left_fork);
//			exit(1);
		}
		pthread_mutex_unlock(&philo->right_philo);
		pthread_mutex_unlock(&philo->right_fork);
		pthread_mutex_unlock(&philo->philo);
//		pthread_mutex_unlock(&philo->left_philo);
		pthread_mutex_unlock(&philo->left_fork);
		ft_str_print(" is sleeping\n", philo);
		usleep(input_philo_array[3] * 1000);
		if (get_current_time() - philo->init > input_philo_array[1])
		{
			error = 1;
			pthread_mutex_unlock(&philo->right_fork);
			pthread_mutex_unlock(&philo->left_fork);
//			exit(1);
		}
		ft_str_print(" is thinking\n", philo);
	}
	return NULL;
}


void thread_func()
{
	pthread_mutex_t mutex[input_philo_array[0]];
	pthread_mutex_t philo_lock[input_philo_array[0]];
	t_thread data[input_philo_array[0]];
	size_t i = 0;
	pthread_t thread[input_philo_array[0]];

	while (i < input_philo_array[0])
	{
		pthread_mutex_init(&philo_lock[i], NULL);
		pthread_mutex_init(&mutex[i], NULL);
		i++;
	}
	i = 0;
	g_time = get_current_time();
	while (i < input_philo_array[0])
	{
		data[i].id = i;
		data[i].right_fork = mutex[i % input_philo_array[0]];
		data[i].left_fork = mutex[i - 1 % input_philo_array[0]];
		data[i].left_philo = philo_lock[i-1 % input_philo_array[0]];
		data[i].right_philo = philo_lock[i+1 % input_philo_array[0]];
		data[i].philo = philo_lock[i % input_philo_array[0]];
		i++;
	}
	i = 0;
	while (i < input_philo_array[0])
	{
		pthread_create(&thread[i], NULL, philo, (void *)&data[i]);
		pthread_detach(thread[i]);
		i += 2;
//		i++;
	}
	i = 1;
	while (i < input_philo_array[0])
	{
		pthread_create(&thread[i], NULL, philo, (void *)&data[i]);
		pthread_detach(thread[i]);
		i += 2;
	}
	while (!error)
	{
		;
	}
	i = 0;
	while (i < input_philo_array[0])
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
    else if (argc == 5)
	{
		input_philo_array = (int *)ft_x_malloc(sizeof(int) * 4);
		while (++i < 4)
			input_philo_array[i] = ft_atoi(argv[i + 1]);
	}
    else
	{
		input_philo_array = (int *)ft_x_malloc(sizeof(int) * 5);
		while (++i < 5)
			input_philo_array[i] = ft_atoi(argv[i + 1]);
	}
	thread_func();
	return (0);
}
