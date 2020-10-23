#include "philo_one.h"
#include "stdio.h"
#include "pthread.h"
#include <unistd.h>
#include <sys/time.h>

int	*input_philo_array;
int error;
time_t g_time;

typedef struct	s_thread
{
	size_t			id;
	pthread_mutex_t left;
	pthread_mutex_t right;
	time_t init;
}				t_thread;

time_t 	get_current_time()
{
	struct timeval tmp_time;
	time_t time;

	gettimeofday(&tmp_time, NULL);
	time = tmp_time.tv_sec * 1000 + tmp_time.tv_usec / 1000;
	return (time);
}

void	*philo(void *data)
{
	t_thread *philo = (t_thread *)data;
	printf("%ld %zu has taken a fork\n", get_current_time() - g_time, philo->id);
	philo->init = get_current_time();
	while (!error)
	{
		pthread_mutex_lock(&philo->left);
		pthread_mutex_lock(&philo->right);
		usleep(input_philo_array[2] * 1000);
		if (get_current_time() - philo->init > input_philo_array[1])
		{
			printf("%ld %zu died\n", get_current_time() - g_time, philo->id);
			error = 1;
			pthread_mutex_unlock(&philo->right);
			pthread_mutex_unlock(&philo->left);
			exit(1);
		}
		printf("%ld %zu is eating\n", get_current_time() - g_time, philo->id);
		philo->init = get_current_time();
		pthread_mutex_unlock(&philo->right);
		pthread_mutex_unlock(&philo->left);
		usleep(input_philo_array[3] * 1000);
		if (get_current_time() - philo->init > input_philo_array[1])
		{
			error = 1;
			pthread_mutex_unlock(&philo->right);
			pthread_mutex_unlock(&philo->left);
			exit(1);
		}
		printf("%ld %zu is sleeping\n", get_current_time() - g_time, philo->id);
		printf("%ld %zu is thinking\n", get_current_time() - g_time, philo->id);
	}
	return NULL;
}


void thread_func()
{
	pthread_mutex_t mutex[input_philo_array[0]];
	t_thread data[input_philo_array[0]];
	size_t i = 0;
	pthread_t thread[input_philo_array[0]];

	while (i < input_philo_array[0])
	{
		pthread_mutex_init(&mutex[i], NULL);
		i++;
	}
	i = 0;
	g_time = get_current_time();
	while (i < input_philo_array[0])
	{
		data[i].id = i;
		data[i].right = mutex[i % input_philo_array[0]];
		data[i].left = mutex[i-1 % input_philo_array[0]];
		i++;
	}
	i = 0;
	while (i < input_philo_array[0])
	{
		pthread_create(&thread[i], NULL, philo, (void *)&data[i]);
		pthread_detach(thread[i]);
		i += 2;
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
