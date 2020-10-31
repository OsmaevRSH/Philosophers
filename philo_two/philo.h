/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_one.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltheresi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/26 15:40:20 by ltheresi          #+#    #+#             */
/*   Updated: 2020/10/26 15:40:22 by ltheresi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_PHILO_H
# define PHILOSOPHERS_PHILO_H
# include "unistd.h"
# include "stdlib.h"
# include "stdio.h"
# include "pthread.h"
# include <unistd.h>
# include <sys/time.h>
# include "string.h"
# include <semaphore.h>
# define NUMBER_OF_PHILOSOPHERS 0
# define TIME_TO_DIE 1
# define TIME_TO_EAT 2
# define TIME_TO_SLEEP 3
# define NUMBER_OF_TIMES_EACH_PHILOSOPHERS_MAST_EAT 4

uint8_t				g_error;
uint32_t			g_time;
uint8_t				g_check_eating;
short				g_input_array[5];
sem_t				*g_semaphore;

typedef struct		s_thread
{
	uint8_t			id;
	uint32_t		init;
	uint16_t		eat_counter;
}					t_thread;

typedef struct		s_print
{
	uint8_t			size;
	uint32_t		time;
	size_t			i;
	size_t			len;
	int32_t			tmp;
	char			*str;
	char			stat_buffer[50];
}					t_print;

int					ft_atoi(const char *str);
time_t				get_current_time();
void				ft_str_print(uint8_t j, t_thread *philo);
void				*check_died(void *ref_time);
void				*philo(void *data);
uint8_t				check_count_of_eating(uint16_t count);
void				sleep_func(unsigned ms_time);

#endif
