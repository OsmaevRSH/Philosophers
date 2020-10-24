#include "philo_one.h"
#include "stdio.h"
#include "pthread.h"
#include <unistd.h>
#include <sys/time.h>

int	*input_philo_array;
int error;
time_t g_time;

typedef struct	s_thread
{
	size_t			id;
	pthread_mutex_t left;
	pthread_mutex_t right;
	time_t init;
	pthread_mutex_t left_philo;
	pthread_mutex_t philo;
	pthread_mutex_t right_philo;
}				t_thread;

time_t 	get_current_time()
{
	struct timeval tmp_time;
	time_t time;

	gettimeofday(&tmp_time, NULL);
	time = tmp_time.tv_sec * 1000 + tmp_time.tv_usec / 1000;
	return (time);
}

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

void	*philo(void *data)
{
	char *out = ft_strdup("");
	t_thread *philo = (t_thread *)data;
	philo->init = get_current_time();
	while (!error)
	{
//		pthread_mutex_lock(&philo->left_philo);
		pthread_mutex_lock(&philo->philo);
		pthread_mutex_lock(&philo->right_philo);
		pthread_mutex_lock(&philo->left);
		out = ft_strjoin_free(out, ft_itoa(get_current_time() - g_time));
		out = ft_strjoin_free(out, " ");
		out = ft_strjoin_free(out, ft_itoa(philo->id));
		out = ft_strjoin_free(out, " has taken a fork\n");
		ft_putstr(out);
		pthread_mutex_lock(&philo->right);
		out = ft_strjoin_free(out, ft_itoa(get_current_time() - g_time));
		out = ft_strjoin_free(out, " ");
		out = ft_strjoin_free(out, ft_itoa(philo->id));
		out = ft_strjoin_free(out, " has taken a fork\n");
		ft_putstr(out);
		out = ft_strjoin_free(out, ft_itoa(get_current_time() - g_time));
		out = ft_strjoin_free(out, " ");
		out = ft_strjoin_free(out, ft_itoa(philo->id));
		out = ft_strjoin_free(out, " is eating\n");
		ft_putstr(out);
		philo->init = get_current_time();
//		printf("%ld %zu has taken a fork\n", get_current_time() - g_time, philo->id);
//		printf("%ld %zu is eating\n", get_current_time() - g_time, philo->id);
		usleep(input_philo_array[2] * 1000);
		if (get_current_time() - philo->init > input_philo_array[1])
		{
			printf("%ld %zu died\n", get_current_time() - g_time, philo->id);
			error = 1;
			pthread_mutex_unlock(&philo->right);
			pthread_mutex_unlock(&philo->left);
			exit(1);
		}
		pthread_mutex_unlock(&philo->right_philo);
		pthread_mutex_unlock(&philo->philo);
//		pthread_mutex_unlock(&philo->left_philo);
		pthread_mutex_unlock(&philo->left);
		pthread_mutex_unlock(&philo->right);
		out = ft_strjoin_free(out, ft_itoa(get_current_time() - g_time));
		out = ft_strjoin_free(out, " ");
		out = ft_strjoin_free(out, ft_itoa(philo->id));
		out = ft_strjoin_free(out, " is sleeping\n");
		ft_putstr(out);
//		printf("%ld %zu is sleeping\n", get_current_time() - g_time, philo->id);
		usleep(input_philo_array[3] * 1000);
		if (get_current_time() - philo->init > input_philo_array[1])
		{
			error = 1;
			pthread_mutex_unlock(&philo->right);
			pthread_mutex_unlock(&philo->left);
			exit(1);
		}
		out = ft_strjoin_free(out, ft_itoa(get_current_time() - g_time));
		out = ft_strjoin_free(out, " ");
		out = ft_strjoin_free(out, ft_itoa(philo->id));
		out = ft_strjoin_free(out, " is thinking\n");
		ft_putstr(out);
//		printf("%ld %zu is thinking\n", get_current_time() - g_time, philo->id);
	}
	return NULL;
}


void thread_func()
{
	pthread_mutex_t mutex[input_philo_array[0]];
	pthread_mutex_t philo_lock[input_philo_array[0]];
	t_thread data[input_philo_array[0]];
	size_t i = 0;
	pthread_t thread[input_philo_array[0]];

	while (i < input_philo_array[0])
	{
		pthread_mutex_init(&philo_lock[i], NULL);
		pthread_mutex_init(&mutex[i], NULL);
		i++;
	}
	i = 0;
	g_time = get_current_time();
	while (i < input_philo_array[0])
	{
		data[i].id = i;
		data[i].right = mutex[i % input_philo_array[0]];
		data[i].left = mutex[i-1 % input_philo_array[0]];
		data[i].left_philo = philo_lock[i-1 % input_philo_array[0]];
		data[i].right_philo = philo_lock[i+1 % input_philo_array[0]];
		data[i].philo = philo_lock[i % input_philo_array[0]];
		i++;
	}
	i = 0;
	while (i < input_philo_array[0])
	{
		pthread_create(&thread[i], NULL, philo, (void *)&data[i]);
		pthread_detach(thread[i]);
//		i += 2;
		i++;
	}
//	i = 1;
//	while (i < input_philo_array[0])
//	{
//		pthread_create(&thread[i], NULL, philo, (void *)&data[i]);
//		pthread_detach(thread[i]);
//		i += 2;
//	}
	while (!error)
	{
		;
	}
	i = 0;
	while (i < input_philo_array[0])
	{
		pthread_mutex_destroy(&mutex[i]);
		i++;
	}
	write(2, "error\n", 6);
}

int		main(int argc, char **argv)
{
	int i;

	i = -1;
    if (argc > 6 || argc < 5)
	{
    	write(2, "Error: invalid count of arguments\n", 34);
		return (1);
	}
    else if (argc == 5)
	{
		input_philo_array = (int *)ft_x_malloc(sizeof(int) * 4);
		while (++i < 4)
			input_philo_array[i] = ft_atoi(argv[i + 1]);
	}
    else
	{
		input_philo_array = (int *)ft_x_malloc(sizeof(int) * 5);
		while (++i < 5)
			input_philo_array[i] = ft_atoi(argv[i + 1]);
	}
	thread_func();
	return (0);
}
