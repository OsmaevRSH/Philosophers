#include "philo_one.h"

void	ft_str_print(char *str, t_thread *philo)
{
	char *out = ft_strdup("");

	out = ft_strjoin_free(out, ft_itoa(get_current_time() - g_time));
	out = ft_strjoin_free(out, " ");
	out = ft_strjoin_free(out, ft_itoa(philo->id));
	out = ft_strjoin_free(out, str);
	ft_putstr(out);
}

//void	*check_died(void *ref_time)
//{
//
//}
