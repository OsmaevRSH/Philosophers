#include "philo_one.h"

static char			*message_array[] = {"has taken a fork\n", "is eating\n", "is sleeping\n", "is thinking\n", "died\n"};
static char			number[] = "0123456789";

time_t get_current_time()
{
	struct timeval			tmp_time;
	unsigned					time;

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


void		ft_str_print(int j, t_thread *philo)
{
	char					stat_buffer[50];
	uint8_t					size;
	uint32_t				time;
	size_t					i;
	size_t					len;
	int						tmp;
	char					*str = (char *)message_array[j];

	memset(stat_buffer, ' ', sizeof(stat_buffer));
	tmp = philo->id;
	time = get_current_time() - g_time;
	size = ft_nlen(time);
	len = size + 1;
	i = -1;

	while (++i < size)
	{
		stat_buffer[size - 1 - i] = number[time % 10];
		time /= 10;
	}
	size = ft_nlen(tmp);
	i = -1;
	while (++i < size)
	{
		stat_buffer[len + size - 1 - i] = number[tmp % 10];
		tmp /= 10;
	}
	len += size + 1;
	while (*str)
		stat_buffer[len++] = *str++;
	write(1, stat_buffer, len);
}
