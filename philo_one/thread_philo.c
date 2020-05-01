#include "philo_one.h"

void	*fn_philo(void *p_data)
{
	node *n;

	n = p_data;
	n->start = current_timestamp();
	if (pthread_create(&(n->monitor_die), NULL, fn_monitor, p_data))
		return (0);
	pthread_detach(n->monitor_die);
	pthread_mutex_lock(n->lock_s);
	ft_putlnbr_fd(n->start, 1);
	write(1, " ", 1);
	ft_putnbr_fd(n->value, 1);
	write(1, " is thinking\n", 14);
	pthread_mutex_unlock(n->lock_s);
	while (1)
	{
		while (!(n->fork_lock == 0 && n->next->fork_lock == 0))
		{
			usleep(10);
		}
		pthread_mutex_lock(&(n->lock));
		n->fork_lock = 1;
		pthread_mutex_lock(&(n->next->lock));
		n->next->fork_lock = 1;
		pthread_mutex_lock(n->lock_s);
		ft_putlnbr_fd(current_timestamp(), 1);
		write(1, " ", 1);
		ft_putnbr_fd(n->value, 1);
		ft_putnbr_fd(n->value, 1);
		write(1, " has taken a fork\n", 18);
		ft_putlnbr_fd(current_timestamp(), 1);
		write(1, " ", 1);
		ft_putnbr_fd(n->value, 1);
		ft_putnbr_fd(n->next->value, 1);
		write(1, " has taken a fork\n", 18);
		pthread_mutex_unlock(n->lock_s);
		n->start = current_timestamp();
		n->count_eat = n->count_eat + 1;
		pthread_mutex_lock(n->lock_s);
		ft_putlnbr_fd(n->start, 1);
		write(1, " ", 1);
		ft_putnbr_fd(n->value, 1);
		ft_putnbr_fd(n->count_eat, 1);
		write(1, " is eating\n", 11);
		pthread_mutex_unlock(n->lock_s);
		usleep(n->tt_eat * 1000);
		n->next->fork_lock = 0;
		pthread_mutex_unlock(&(n->next->lock));
		n->fork_lock = 0;
		pthread_mutex_unlock(&(n->lock));
		if (n->count_eat == n->nb_eat)
			while (1)
			{
				usleep(5000 * 1000)
			}
		pthread_mutex_lock(n->lock_s);
		ft_putlnbr_fd(current_timestamp(), 1);
		write(1, " ", 1);
		ft_putnbr_fd(n->value, 1);
		write(1, " is sleeping\n", 13);
		pthread_mutex_unlock(n->lock_s);
		usleep(n->tt_sleep * 1000);
		pthread_mutex_lock(n->lock_s);
		ft_putlnbr_fd(current_timestamp(), 1);
		write(1, " ", 1);
		ft_putnbr_fd(n->value, 1);
		write(1, " is thinking\n", 14);
		pthread_mutex_unlock(n->lock_s);
	}
	return (0);
}