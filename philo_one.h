#ifndef PHILOSOPHERS_PHILO_ONE_H
#define PHILOSOPHERS_PHILO_ONE_H

#include "unistd.h"
# include "stdlib.h"
# include "stdio.h"
# include "pthread.h"
# include <unistd.h>
# include <sys/time.h>
# include "string.h"
# define NUMBER_OF_PHILOSOPHERS 0
# define TIME_TO_DIE 1
# define TIME_TO_EAT 2
# define TIME_TO_SLEEP 3
# define NUMBER_OF_TIMES_EACH_PHILOSOPHERS_MAST_EAT 4

int					*input_philo_array;
uint8_t				error;
unsigned			g_time;

typedef struct		s_thread
{
	uint8_t			id;
	pthread_mutex_t left_fork;
	pthread_mutex_t right_fork;
	unsigned		init;
}					t_thread;

int					ft_atoi(const char *str);
time_t				get_current_time();
void				ft_str_print(int j, t_thread *philo);
void				*check_died(void *ref_time);

#endif
