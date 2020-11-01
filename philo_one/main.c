/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltheresi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/26 18:46:29 by ltheresi          #+#    #+#             */
/*   Updated: 2020/10/26 18:46:31 by ltheresi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	init_mutex_struct(t_thread *data,
		pthread_mutex_t *mutex)
{
	short i;

	i = -1;
	while (++i < g_input_array[NUMBER_OF_PHILOSOPHERS])
		pthread_mutex_init(&(mutex[i]), NULL);
	i = 0;
	data[0].id = 0;
	data[0].left_fork = &mutex[0];
	data[0].right_fork = &mutex[g_input_array[NUMBER_OF_PHILOSOPHERS] - 1];
	data[0].eat_counter = 0;
	while (++i < g_input_array[NUMBER_OF_PHILOSOPHERS])
	{
		data[i].id = i;
		data[i].right_fork = &mutex[i];
		data[i].left_fork = &mutex[i - 1 < 0 ?
		g_input_array[NUMBER_OF_PHILOSOPHERS] - 1 : i - 1];
		data[i].eat_counter = 0;
	}
	g_time = get_current_time();
}

void	thread_func(void)
{
	pthread_mutex_t	*mutex;
	t_thread		*data;
	pthread_t		*thread;
	short			i;

	mutex = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t)
	* g_input_array[NUMBER_OF_PHILOSOPHERS]);
	data = (t_thread *)malloc(sizeof(t_thread)
	* g_input_array[NUMBER_OF_PHILOSOPHERS]);
	thread = (pthread_t *)malloc(sizeof(pthread_t)
	* g_input_array[NUMBER_OF_PHILOSOPHERS]);
	init_mutex_struct(data, mutex);
	i = -1;
	while (++i < g_input_array[NUMBER_OF_PHILOSOPHERS])
		pthread_create(&thread[i], NULL, philo, (void *)&data[i]);
	while (!g_error && !g_check_eating)
		;
	while (--i >= 0)
		pthread_join(thread[i], NULL);
	while (++i < g_input_array[NUMBER_OF_PHILOSOPHERS])
		pthread_mutex_destroy(&mutex[i]);
	free(mutex);
	free(data);
	free(thread);
}

int		main(int argc, char **argv)
{
	int8_t i;

	i = -1;
	if (argc > 6 || argc < 5)
	{
		write(2, "Error: invalid count of arguments\n", 34);
		return (1);
	}
	if (argc == 5)
	{
		while (++i < 4)
			g_input_array[i] = ft_atoi(argv[i + 1]);
		g_check_eating = 0;
	}
	else
	{
		while (++i < 5)
			g_input_array[i] = ft_atoi(argv[i + 1]);
		g_check_eating = 1;
	}
	thread_func();
	return (0);
}