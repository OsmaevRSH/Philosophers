#ifndef PHILOSOPHERS_PHILO_ONE_H
#define PHILOSOPHERS_PHILO_ONE_H

#include "unistd.h"
# include "stdlib.h"
# include "stdio.h"
# include "pthread.h"
# include <unistd.h>
# include <sys/time.h>
# define NUMBER_OF_PHILOSOPHERS 0
# define TIME_TO_DIE 1
# define TIME_TO_EAT 2
# define TIME_TO_SLEEP 3
# define NUMBER_OF_TIMES_EACH_PHILOSOPHERS_MAST_EAT 4

int					*input_philo_array;
int					error;
time_t				g_time;
//int					check_count_of_eat;

typedef struct		s_thread
{
	size_t			id;
	pthread_mutex_t left_fork;
	pthread_mutex_t right_fork;
	time_t			init;
	size_t			eat;
}					t_thread;

void				*ft_x_malloc(size_t size);
int					ft_atoi(const char *str);
time_t				get_current_time();
void				ft_str_print(const char *str, t_thread *philo);
void				*check_died(void *ref_time);

#endif
