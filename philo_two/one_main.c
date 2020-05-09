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
			sem_post(n->sem_die);
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
		usleep(10 * 000);
		if (current_timestamp() - n->start > n->tt_die && \
n->count_eat != n->nb_eat)
		{
			ft_message(n, " died\n", current_timestamp(), 5);
			sem_post(n->sem_die);
			break;
		}
	}
	return (0);
}

int			main(int ac, char **av)
{
	int		i;
	bin		var;
	void	*t;
	char	*str;

	if (ft_arg(&var, ac, av))
		return (1);
	str = malloc(sizeof(char) * 3);
	str[0] = 'd';
	str[1] = '\0';
	sem_unlink(str);
	var.sem_die = sem_open(str, O_CREAT | O_EXCL, 0664, 1);
	sem_wait(var.sem_die);
	if (ft_create(&var))
		return (1);
	i = 1;
	while (i < var.nb + 1)
	{
		t = &(var.philo[i]);
		if (pthread_create(&(var.philo[i].thread), NULL, fn_philo, t))
			return (ft_clear_mutex(&var, var.nb));
		pthread_detach(var.philo[i].thread);
		i++;
	}
	t = &(var.philo[1]);
	if (pthread_create(&(var.philo[1].thread), NULL, fn_monitor_eat, t))
		return (ft_clear_mutex(&var, var.nb));
	pthread_detach(var.philo[i].thread);
	sem_wait(var.sem_die);
	return (ft_clear_mutex(&var, var.nb));
}
