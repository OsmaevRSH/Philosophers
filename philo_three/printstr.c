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

#include "philo.h"

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

void		print_init(t_print *print, t_thread *philo, uint8_t j)
{
	print->str = g_message_array[j];
	memset(print->stat_buffer, ' ', sizeof(print->stat_buffer));
	print->tmp = philo->id;
	print->time = get_current_time() - g_time;
	print->size = ft_nlen(print->time);
	print->len = print->size + 1;
	print->i = -1;
}

void		ft_str_print(uint8_t j, t_thread *philo)
{
	t_print					print;

	j == 1 ? philo->eat_counter += 1 : 0;
	print_init(&print, philo, j);
	while (++print.i ^ print.size)
	{
		print.stat_buffer[print.size - 1 - print.i] = g_number[print.time % 10];
		print.time /= 10;
	}
	print.size = ft_nlen(print.tmp);
	print.i = -1;
	while (++print.i ^ print.size)
	{
		print.stat_buffer[print.len +
		print.size - 1 - print.i] = g_number[print.tmp % 10];
		print.tmp /= 10;
	}
	while (*print.str)
		print.stat_buffer[print.len++ + print.size + 1] = *print.str++;
	write(1, print.stat_buffer, print.len + print.size + 1);
}
