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

void	init_mutex_struct(t_thread *data)
{
	short i;

	i = -1;
	if (!(semaphore = sem_open("forks_semaphore", O_CREAT | O_TRUNC , 0666, g_input_array[NUMBER_OF_PHILOSOPHERS])))
	{
		write(2, "error", 5);
		exit(1);
	}
	while (++i < g_input_array[NUMBER_OF_PHILOSOPHERS])
	{
		data[i].id = i;
		data[i].eat_counter = 0;
	}
	g_time = get_current_time();
}

void	thread_func(void)
{
	t_thread		data[g_input_array[NUMBER_OF_PHILOSOPHERS]];
	pthread_t		thread[g_input_array[NUMBER_OF_PHILOSOPHERS]];
	short			i;

	init_mutex_struct((t_thread *)&data);
	i = -2;
	while ((i += 2) < g_input_array[NUMBER_OF_PHILOSOPHERS])
		pthread_create(&thread[i], NULL, philo, (void *)&data[i]);
	sleep_func(g_input_array[TIME_TO_SLEEP]);
	i = -1;
	while ((i += 2) < g_input_array[NUMBER_OF_PHILOSOPHERS])
		pthread_create(&thread[i], NULL, philo, (void *)&data[i]);
	if (!g_check_eating)
		while (!g_error)
			;
	i = 0;
	while (i < g_input_array[NUMBER_OF_PHILOSOPHERS])
		pthread_join(thread[i++], NULL);
	sem_close(semaphore);
	sem_unlink("forks_semaphore");
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