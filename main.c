#include "philo_one.h"
#include "stdio.h"
#include "pthread.h"

pthread_mutex_t mutex;

typedef struct	s_thread
{
	size_t		id;
}				t_thread;

void *one(void *data)
{
	pthread_mutex_lock(&mutex);
	t_thread *tmp = (t_thread *)data;
	printf("%zu ONE\n", tmp->id);
	pthread_mutex_unlock(&mutex);
	return 0;
}

void *two(void *data)
{
	pthread_mutex_lock(&mutex);
	t_thread *tmp = (t_thread *)data;
	printf("%zu TWO\n", tmp->id);
	pthread_mutex_unlock(&mutex);
	return 0;
}


void thread_func()
{
	t_thread data[10];
	int i = 0;
	pthread_t thread[10];

	pthread_mutex_init(&mutex, NULL);
	while (i < 10)
	{
		data[i].id = i;
		i++;
	}
	i = 0;
	while (i < 5)
	{
		pthread_create(&thread[i], NULL, &one, (void *)&data[i]);
		i++;
	}
	while (i < 10)
	{
		pthread_create(&thread[i], NULL, &two, (void *)&data[i]);
		i++;
	}
	i = 0;
	while (i < 10)
	{
		pthread_join(thread[i], NULL);
		i++;
	}
	pthread_mutex_destroy(&mutex);
}

int		main(int argc, char **argv)
{
//	int	*input_philo_array;
//	int i;
//
//	i = -1;
//    if (argc > 6 || argc < 5)
//	{
//    	write(2, "Error: invalid count of arguments\n", 34);
//		return (1);
//	}
//    else if (argc == 5)
//	{
//		input_philo_array = (int *)ft_x_malloc(sizeof(int) * 4);
//		while (++i < 4)
//			input_philo_array[i] = ft_atoi(argv[i + 1]);
//		a = 1;
//	}
//    else
//	{
//		input_philo_array = (int *)ft_x_malloc(sizeof(int) * 5);
//		while (++i < 5)
//			input_philo_array[i] = ft_atoi(argv[i + 1]);
//	}
	thread_func();
	return (0);
}
