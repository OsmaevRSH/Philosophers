#include "philo_one.h"

int						ft_atoi(const char *str)
{
	int					sign;
	unsigned long long	sum;

	sign = 1;
	sum = 0;
	while (*str == ' ' || *str == '\t' || *str == '\n' || \
		*str == '\r' || *str == '\f' || *str == '\v')
		str++;
	while (*str >= '0' && *str <= '9')
	{
		sum = sum * 10 + (*str - 48);
		str++;
	}
	return ((int)(sign * sum));
}
