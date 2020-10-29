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
	if (!(semaphore = sem_open("forks_semaphore", O_CREAT , 0666, g_input_array[NUMBER_OF_PHILOSOPHERS])))
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
	t_thread		*data = (t_thread *)malloc(sizeof(t_thread) * g_input_array[NUMBER_OF_PHILOSOPHERS]);
	pid_t			*pid_array = (pid_t *)malloc(sizeof(pid_t) * g_input_array[NUMBER_OF_PHILOSOPHERS]);
	short			i;
	int				status;

	sem_unlink("forks_semaphore");
	init_mutex_struct(data);
	i = -1;
	while (++i < g_input_array[NUMBER_OF_PHILOSOPHERS])
	{
		if ((pid_array[i] = fork() < 0))
			exit(1);
		if (!pid_array[i])
		{
			philo(&data[i]);
			exit(0);
		}
	}
	waitpid(-1, &status, 0);
	i = -1;
	if (WEXITSTATUS(status) == 1)
	{
		while (++i < g_input_array[NUMBER_OF_PHILOSOPHERS])
			kill(pid_array[i], SIGKILL);
	}
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
