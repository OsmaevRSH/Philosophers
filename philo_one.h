#ifndef PHILOSOPHERS_PHILO_ONE_H
#define PHILOSOPHERS_PHILO_ONE_H

#include "unistd.h"
# include "stdlib.h"
# include "stdio.h"
# include "pthread.h"
# include <unistd.h>
# include <sys/time.h>

int					*input_philo_array;
int					error;
time_t				g_time;

typedef struct		s_thread
{
	size_t			id;
	pthread_mutex_t left;
	pthread_mutex_t right;
	time_t			init;
	pthread_mutex_t left_philo;
	pthread_mutex_t philo;
	pthread_mutex_t right_philo;
}					t_thread;

void				*ft_x_malloc(size_t size);
int					ft_atoi(const char *str);
char				*ft_itoa(long n);
void				ft_putstr(char *str);
char				*ft_strjoin_free(char *s1, char *s2);
char				*ft_strdup(const char *s1);
time_t				get_current_time();
void				ft_str_print(char *str, t_thread *philo);
void				*check_died(void *ref_time);

#endif
