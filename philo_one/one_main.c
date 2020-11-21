#include "philo_one.h"

long long	current_timestamp(void)
{
	struct timeval	te;
	long long		m;

	gettimeofday(&te, NULL);
	m = te.tv_sec * 1000LL + te.tv_usec / 1000;
	return (m);
}

void		*fn_monitor_eat(void *p_data)
{
	node	*n;
	int		nb_eat_total;
	int		i;

	n = p_data;
	while (1)
	{
		usleep(10 * 1000);
		nb_eat_total = 0;
		i = 1;
		while (i < n->nb + 1)
		{
			nb_eat_total = nb_eat_total + n->count_eat;
			n = n->next;
			i++;
		}
		if (nb_eat_total == n->nb * n->nb_eat)
		{
			pthread_mutex_unlock(n->lock_die);
			return (0);
		}
	}
	return (0);
}

void		*fn_monitor(void *p_data)
{
	node *n;

	n = p_data;
	while (1)
	{
		usleep(2000);
		if (current_timestamp() - n->start > n->tt_die && \
n->count_eat != n->nb_eat)
		{
			pthread_mutex_lock(n->lock_s);
			ft_putlnbr_fd(current_timestamp(), 1);
			write(1, " ", 1);
			ft_putlnbr_fd(n->start, 1);
			write(1, " ", 1);
			ft_putnbr_fd(n->value, 1);
			write(1, " has died\n", 10);
			pthread_mutex_unlock(n->lock_die);
			return (0);
		}
	}
	return (0);
}

int			main(int ac, char **av)
{
	int		i;
	bin		var;
	void	*t;

	if (ft_arg(&var, ac, av))
		return (1);
	if (ft_create(&var))
		return (1);
	pthread_mutex_lock(&(var.lock_die));
	i = 1;
	while (i < var.nb + 1)
	{
		t = &(var.philo[i]);
		pthread_mutex_lock(&(var.lock_crea));
		if (pthread_create(&(var.philo[i].thread), NULL, fn_philo, t))
			return (ft_clear_mutex(&var, var.nb));
		pthread_detach(var.philo[i].thread);
		pthread_mutex_lock(&(var.lock_crea));
		pthread_mutex_unlock(&(var.lock_crea));
		usleep(50);
		i++;
	}
	t = &(var.philo[1]);
	if (pthread_create(&(var.philo[1].thread), NULL, fn_monitor_eat, t))
		return (ft_clear_mutex(&var, var.nb));
	pthread_detach(var.philo[1].thread);
	pthread_mutex_lock(&(var.lock_die));
	pthread_mutex_unlock(&(var.lock_die));
	return (ft_clear_mutex(&var, var.nb));
}
