#include "philo_one.h"

int						ft_atoi(const char *str)
{
	int					sign;
	unsigned long long	sum;
	int					cout;

	sign = 1;
	sum = 0;
	cout = 0;
	while (*str == ' ' || *str == '\t' || *str == '\n' || \
		*str == '\r' || *str == '\f' || *str == '\v')
		str++;
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			sign = -1;
		str++;
	}
	while (*str >= '0' && *str <= '9')
	{
		sum = sum * 10 + (*str - 48);
		str++;
		cout++;
	}
	if (sum > 9223372036854775807 || cout > 19)
		return (sign == -1) ? 0 : -1;
	return ((int)(sign * sum));
}
