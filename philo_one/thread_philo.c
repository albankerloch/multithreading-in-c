#include "philo_one.h"

void		ft_message(node *n, char *str, long long tm)
{
	int i;
	int k;
	int b;

	pthread_mutex_lock(n->lock_s);
	ft_putlnbr_mess(n, tm, 12);
	n->mess[13] = ' ';
	b = n->value;
	k = 0;
	while ((b % 10) != b)
	{
		b = b / 10;
		k++;
	}
	b = n->value;
	ft_putlnbr_mess(n, n->value, 14 + k);
	i = 0;
	while (str[i])
	{
		n->mess[i + 15 + k] = str[i] ;
		i++;
	}
	n->mess[i + 15 + k] = '\0';
	write(1, n->mess, ft_strlen(n->mess));
	pthread_mutex_unlock(n->lock_s);
}

time_t	get_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}

void	ft_sleep(int n)
{
	time_t start;

	start = get_time();
	while ((get_time() - start) < n)
		usleep(200);
}

static void	ft_activity(node *n)
{
	pthread_mutex_lock(&(n->lock));
	ft_message(n, " has taken a fork\n", current_timestamp());
	pthread_mutex_lock(&(n->next->lock));
	ft_message(n, " has taken a fork\n", current_timestamp());
	n->start = current_timestamp();
	n->count_eat = n->count_eat + 1;
	ft_message(n, " is eating\n", n->start);
	ft_sleep(n->tt_eat);
	pthread_mutex_unlock(&(n->next->lock));
	pthread_mutex_unlock(&(n->lock));
	if (n->count_eat == n->nb_eat)
	{
		while (1)
		{
			usleep(5000 * 1000);
		}
	}
	ft_message(n, " is sleeping\n", current_timestamp());
	ft_sleep(n->tt_sleep);
	ft_message(n, " is thinking\n", current_timestamp());
}

void		*fn_philo(void *p_data)
{
	node *n;

	n = p_data;
	n->start = current_timestamp();
	if (pthread_create(&(n->monitor_die), NULL, fn_monitor, p_data))
		return (0);
	pthread_detach(n->monitor_die);
	pthread_mutex_unlock(n->lock_c);
	ft_message(n, " is thinking\n", n->start);
	while (1)
		ft_activity(n);
	return (0);
}
