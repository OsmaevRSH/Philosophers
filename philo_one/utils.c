/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltheresi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/26 18:23:52 by ltheresi          #+#    #+#             */
/*   Updated: 2020/11/02 01:23:00 by ltheresi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*check_died(void *tmp_philo)
{
	t_thread	*philo;

	philo = (t_thread *)tmp_philo;
	while (!g_error || (g_check_eating && philo->eat_counter
	^ g_input_array[NUMBER_OF_TIMES_EACH_PHILOSOPHERS_MAST_EAT]))
	{
		if ((get_current_time() - philo->init > g_input_array[TIME_TO_DIE]
		&& g_check_eating && philo->eat_counter ^
		g_input_array[NUMBER_OF_TIMES_EACH_PHILOSOPHERS_MAST_EAT]) ||
		(get_current_time() - philo->init > g_input_array[TIME_TO_DIE]
		&& !g_check_eating))
		{
			pthread_mutex_unlock(philo->right_fork);
			pthread_mutex_unlock(philo->left_fork);
			ft_str_print(4, philo);
		}
	}
	return (NULL);
}

void	sleep_func(unsigned ms_time)
{
	unsigned	stop_time;

	stop_time = get_current_time() + ms_time;
	while (get_current_time() ^ stop_time)
		usleep(200);
}

uint8_t	check_count_of_eating(uint16_t count)
{
	if (g_check_eating && !(count ^
	g_input_array[NUMBER_OF_TIMES_EACH_PHILOSOPHERS_MAST_EAT]))
		return (0);
	if (g_error)
		return (0);
	return (1);
}

int		philo_event(t_thread *philo)
{
	pthread_mutex_lock(philo->left_fork);
	if (ft_str_print(0, philo))
		return (1);
	pthread_mutex_lock(philo->right_fork);
	if (ft_str_print(0, philo))
		return (1);
	philo->init = get_current_time();
	if (ft_str_print(1, philo))
		return (1);
	sleep_func(g_input_array[TIME_TO_EAT]);
	pthread_mutex_unlock(philo->right_fork);
	pthread_mutex_unlock(philo->left_fork);
	if (ft_str_print(2, philo))
		return (1);
	sleep_func(g_input_array[TIME_TO_SLEEP]);
	if (ft_str_print(3, philo))
		return (1);
	return (0);
}

void	*philo(void *data)
{
	pthread_t	died;
	t_thread	*philo;

	philo = (t_thread *)data;
	if ((philo->id & 1) == 1)
		sleep_func(g_input_array[TIME_TO_SLEEP]);
	pthread_create(&died, NULL, check_died, (void *)philo);
	philo->init = get_current_time();
	while (check_count_of_eating(philo->eat_counter))
	{
		if (philo_event(philo))
			return (NULL);
	}
	return (NULL);
}
