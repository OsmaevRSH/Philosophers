#include "philo_one.h"

time_t		get_current_time()
{
	struct timeval			tmp_time;
	time_t					time;

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


void		ft_str_print(const char *str, t_thread *philo)
{
	char					stat_buffer[50];
	uint8_t					size;
	uint32_t				time;
	size_t					i;
	size_t					len;
	int						tmp;

	i = 0;
	while (i < 50)
		stat_buffer[i++] = ' ';
	tmp = philo->id;
	time = get_current_time() - g_time;
	size = ft_nlen(time);
	len = size + 1;
	i = -1;
	while (++i < size)
	{
		stat_buffer[size - 1 - i] = (char)((time % 10) + '0');
		time /= 10;
	}
	size = ft_nlen(tmp);
	i = -1;
	while (++i < size)
	{
		stat_buffer[len + size - 1 - i] = (char)((tmp % 10) + '0');
		tmp /= 10;
	}
	len += size + 1;
	i = -1;
	while (str[++i])
		stat_buffer[len + i] = str[i];
	write(1, stat_buffer, len + i);
}
