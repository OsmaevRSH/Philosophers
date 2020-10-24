#include "philo_one.h"

size_t  ft_strlen(const char *str)
{
	int i = 0;
	if (!str)
		return (0);
	while (str[i])
		i++;
	return (i);
}

void	ft_putstr(char *str)
{
	write(1, str, ft_strlen(str));
}

static int		ft_count(long long tmp_n)
{
	int			len;

	len = 0;
	if (tmp_n == 0)
		return (1);
	if (tmp_n < 0)
		len++;
	while (tmp_n)
	{
		tmp_n /= 10;
		len++;
	}
	return (len);
}

char			*ft_itoa(long n)
{
	char		*str;
	int			len;
	long long	tmp_n;

	tmp_n = (long long int)n;
	len = ft_count(tmp_n);
	if (!(str = (char *)malloc(sizeof(char) * (len + 1))))
		return (0);
	str[len--] = '\0';
	if (tmp_n < 0)
	{
		str[0] = '-';
		tmp_n *= -1;
	}
	while (tmp_n > 9)
	{
		str[len--] = (char)((tmp_n % 10) + 48);
		tmp_n /= 10;
	}
	str[len] = (char)(tmp_n + 48);
	return (str);
}

char				*ft_strjoin_free(char *s1, char *s2)
{
	char			*str;
	char			*tmp_str;
	char			*tmp_s1;

	tmp_s1 = s1;
	if (!s1 || !s2)
		return (0);
	if (!(str = (char *)malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1))))
		return (0);
	tmp_str = str;
	while (*s1)
		*str++ = *s1++;
	while (*s2)
		*str++ = *s2++;
	*str = '\0';
	free(tmp_s1);
	return (tmp_str);
}

char		*ft_strdup(const char *s1)
{
	char	*new_str;
	size_t	len_str;
	size_t	i;

	len_str = ft_strlen(s1);
	i = 0;
	if (!(new_str = (char *)malloc((len_str + 1) * sizeof(char))))
		return (0);
	while (s1[i])
	{
		new_str[i] = s1[i];
		i++;
	}
	new_str[i] = '\0';
	return (new_str);
}