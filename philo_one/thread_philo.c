#include "philo_one.h"

void		ft_message(node *n, char *str, long long tm)
{
	pthread_mutex_lock(n->lock_s);
	ft_putlnbr_fd(tm, 1);
	write(1, " ", 1);
	ft_putnbr_fd(n->value, 1);
	write(1, str, ft_strlen(str));
	pthread_mutex_unlock(n->lock_s);
}

static void	ft_activity(node *n)
{
	pthread_mutex_lock(&(n->lock));
	n->fork_lock = 1;
	ft_message(n, " has taken a fork\n", current_timestamp());
	pthread_mutex_lock(&(n->next->lock));
	n->next->fork_lock = 1;
	ft_message(n, " has taken a fork\n", current_timestamp());
	n->start = current_timestamp();
	n->count_eat = n->count_eat + 1;
	ft_message(n, " is eating\n", n->start);
	usleep(n->tt_eat * 1000);
	n->next->fork_lock = 0;
	pthread_mutex_unlock(&(n->next->lock));
	n->fork_lock = 0;
	pthread_mutex_unlock(&(n->lock));
	if (n->count_eat == n->nb_eat)
		while (1)
		{
			usleep(5000 * 1000);
		}
	ft_message(n, " is sleeping\n", current_timestamp());
	usleep(n->tt_sleep * 1000);
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
	ft_message(n, " is thinking\n", n->start);
	while (1)
		ft_activity(n);
	return (0);
}
