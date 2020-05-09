#include "philo_one.h"

void print_value(sem_t *sem_die, int *val)
{
	sem_getvalue(sem_die, val);
	//write(1, "\n", 1);
	//ft_putnbr_fd(*val, 1);
	//write(1, "\n", 1);
}

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
			write(1, "\nP\n", 3);
			sem_wait(n->sem_die2);
			write(1, "\nL\n", 3);
			sem_wait(n->sem_die);
			write(1, "\nS\n", 3);
			//pthread_mutex_unlock(n->lock_die);
			return (0);
		}
	}
	return (0);
}

void		*fn_monitor(void *p_data)
{
	node *n;
	int val;

	n = p_data;
	print_value(n->sem_die, &val);
	//printf("\nMONITOR->%p\n", n->sem_die);
	while (1)
	{
		usleep(10 * 000);
		if (current_timestamp() - n->start > n->tt_die && \
n->count_eat != n->nb_eat)
		{
			pthread_mutex_lock(n->lock_s);
			ft_putlnbr_fd(current_timestamp(), 1);
			write(1, " ", 1);
			//ft_putlnbr_fd(n->start, 1);
			//write(1, " ", 1);
			ft_putnbr_fd(n->value, 1);
			write(1, " has died\n", 10);
			//pthread_mutex_unlock(n->lock_s);
			//pthread_mutex_unlock(n->lock_die);
			print_value(n->sem_die, &val);
			sem_post(n->sem_die);
			/*while (1)
			{
				print_value(n->sem_die, &val);
				write(1, "\nM\n", 3);
				usleep(5000);
			}*/
			write(1, "\nP\n", 3);
			sem_wait(n->sem_die2);
			write(1, "\nL\n", 3);
			sem_wait(n->sem_die);
			write(1, "\nS\n", 3);
			break;
		}
	//write(1, "\nt\n", 3);
	}
	write(1, "\ne\n", 3);
	return (0);
}

int			main(int ac, char **av)
{
	int		i;
	bin		var;
	void	*t;
	char	*str;
	char	*str2;
	int val;

	if (ft_arg(&var, ac, av))
		return (1);
	str = malloc(sizeof(char) * 3);
	str[0] = 'd';
	str[1] = '\0';
	sem_unlink(str);
	var.sem_die = sem_open(str, O_CREAT | O_EXCL, 0664, 1);
	str2 = malloc(sizeof(char) * 3);
	str2[0] = '2';
	str2[1] = '\0';
	sem_unlink(str2);
	var.sem_die2 = sem_open(str2, O_CREAT | O_EXCL, 0664, 1);
	//printf("\n->%p\n", var.sem_die2);
	print_value(var.sem_die, &val);
	sem_wait(var.sem_die);
	sem_wait(var.sem_die2);
	//print_value(var.sem_die, &val);
	if (ft_create(&var))
		return (1);
	//pthread_mutex_lock(&(var.lock_die));
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
	//pthread_mutex_lock(&(var.lock_die));
	//pthread_mutex_unlock(&(var.lock_die));
	//write(1, "\nV\n", 3);
	print_value(var.sem_die, &val);
	sem_wait(var.sem_die);
	print_value(var.sem_die, &val);
	/*while (val == 0)
	{
		write(1, "\nN\n", 3);
		sem_wait(var.sem_die);
		usleep(5000);
		print_value(var.sem_die, &val);
	}*/
	//write(1, "\n\nX\n\n", 5);
	//sem_post(var.sem_die);
	return (ft_clear_mutex(&var, var.nb));
}
