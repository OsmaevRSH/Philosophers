/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printstr.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltheresi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/26 15:38:12 by ltheresi          #+#    #+#             */
/*   Updated: 2020/10/26 15:38:15 by ltheresi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

char				*g_message_array[] = {"has taken a fork\n", \
	"is eating\n", "is sleeping\n", "is thinking\n", "died\n"};
char				g_number[] = "0123456789";

time_t		get_current_time(void)
{
	struct timeval			tmp_time;
	uint32_t				time;

	gettimeofday(&tmp_time, NULL);
	time = tmp_time.tv_sec * 1000 + tmp_time.tv_usec / 1000;
	return (time);
}

uint8_t		ft_nlen(uint32_t n)
{
	int						i;
	static const uint32_t	hash_table[] = { 1000000000, 100000000, 10000000,
	1000000, 100000, 10000, 1000, 100, 10, 0 };

	i = -1;
	while (hash_table[++i])
	{
		if (n >= hash_table[i])
			return (10 - i);
	}
	return (1);
}

void		ft_str_print(uint8_t j, t_thread *philo)
{
	t_print					pr;

	j == 1 ? philo->eat_counter += 1 : 0;
	pr.str = g_message_array[j];
	memset(pr.stat_buffer, ' ', sizeof(pr.stat_buffer));
	pr.tmp = philo->id;
	pr.time = get_current_time() - g_time;
	pr.size = ft_nlen(pr.time);
	pr.len = pr.size + 1;
	pr.i = -1;
	while (++pr.i ^ pr.size)
	{
		pr.stat_buffer[pr.size - 1 - pr.i] = g_number[pr.time % 10];
		pr.time /= 10;
	}
	pr.size = ft_nlen(pr.tmp);
	pr.i = -1;
	while (++pr.i ^ pr.size)
	{
		pr.stat_buffer[pr.len + pr.size - 1 - pr.i] = g_number[pr.tmp % 10];
		pr.tmp /= 10;
	}
	while (*pr.str)
		pr.stat_buffer[pr.len++ + pr.size + 1] = *pr.str++;
	write(1, pr.stat_buffer, pr.len + pr.size + 1);
}
