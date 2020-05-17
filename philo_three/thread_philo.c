#include "philo_one.h"

void		ft_chg_str( char *str_txt, unsigned int t, unsigned int j, char str[50])
{
	unsigned int i;
	
	i = 0;
	while (i < j)
	{
		str[i + t] = str_txt[i];
		i++;
	}
	str[i + t ] = '\n';
	str[i + t + 1] = '\0';
}


void		ft_message(int i, char *str_txt, long long tm, unsigned int j, char str[50])
{
	unsigned int t;

	ft_putlnbr_str(tm, str);
	str[13] = '\0';
	str[13] = ' ';
	ft_putnbr_str(i, str);
	t = ft_strlen(str);
	str[t] = ' ';
	ft_chg_str(str_txt, t, j, str);
	write(1, str, ft_strlen(str));
}


void	ft_activity(int i, char str[50], long long *start, bin *var, sem_t *sem_fork)
{
	ft_message(i, " has taken a fork\n", current_timestamp(), 17, str);
	ft_message(i, " has taken a fork\n", current_timestamp(), 17, str);
	*start = current_timestamp();
	var->count_eat = var->count_eat + 1;
	ft_message(i, " is eating\n", *start, 10, str);
	usleep(var->time_to_eat * 1000);
	sem_post(sem_fork);
	sem_post(sem_fork);
	if (var->count_eat == var->nb_eat)
		while (1)
		{
			usleep(5000 * 1000);
		}
	ft_message(i, " is sleeping\n", current_timestamp(), 12, str);
	usleep(var->time_to_sleep * 1000);
	ft_message(i, " is thinking\n", current_timestamp(), 12, str);
}
/*
void		*fn_philo(void *p_data)
{
	node *n;

	n = p_data;
	n->start = current_timestamp();
	if (pthread_create(&(n->monitor_die), NULL, fn_monitor, p_data))
		return (0);
	ft_message(n, " is thinking\n", n->start, 12);
	while (1)
	{
		sem_wait(n->var->sem_fork);
		sem_wait(n->var->sem_fork);
		ft_activity(n);
	}
	return (0);
}
*/

