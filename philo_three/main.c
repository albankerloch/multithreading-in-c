/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akerloc- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/08 19:55:49 by akerloc-          #+#    #+#             */
/*   Updated: 2019/10/07 16:39:58 by akerloc-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_three.h"

long long	current_timestamp(void)
{
	struct timeval	te;
	long long		m;

	gettimeofday(&te, NULL);
	m = te.tv_sec * 1000LL + te.tv_usec / 1000;
	return (m);
}

void		*fn_monitor(void *p_data)
{
	t_node *n;
	int i;

	n = p_data;
	while (1)
	{
		usleep(10 * 000);
		if (current_timestamp() - n->start > n->tt_die && \
n->count_eat != n->nb_eat)
		{
			ft_message(n, " died\n", n->start, 5);
			i = 1;
			while (i < n->var->nb + 1)
			{
				sem_post(n->sem_die);
				i++;
			}
			break;
		}
	}
	return (0);
}

static int 	routine(t_node *n)
{
	void *p;

	p = (void *)n;
	n->start = current_timestamp();
	if (pthread_create(&(n->monitor_die), NULL, fn_monitor, p))
		return (0);
	pthread_detach(n->monitor_die);
	ft_message(n, " is thinking\n", n->start, 12);
	while (1)
	{
		sem_wait(n->var->sem_fork);
		sem_wait(n->var->sem_fork);
		ft_activity(n);
	}
	return (0);
}

int			main(int ac, char **av)
{
	int		i;
	t_bin		var;

	if (ft_arg(&var, ac, av))
		return (1);

	var.str_fork[0] = 'f';
	var.str_fork[1] = '\0';
	sem_unlink(var.str_fork);
	var.sem_fork = sem_open(var.str_fork, O_CREAT | O_EXCL, 0664, var.nb);
	var.str_die[0] = 'd';
	var.str_die[1] = '\0';
	sem_unlink(var.str_die);
	var.sem_die = sem_open(var.str_die, O_CREAT | O_EXCL, 0664, 1);

	if (ft_create(&var))
		return (1);

	i = 1;
	while (i < var.nb + 1)
	{
		var.philo[i].pid = fork();
		if (var.philo[i].pid < 0)
			return (1);
		else if (var.philo[i].pid == 0)
		{
			routine(&var.philo[i]);
			exit(0);
		}
		usleep(100);
		printf("[%d] [%d] hi i=%d fork=%d\n", getppid(), getpid(), i, var.philo[i].pid);
		i++;
	}
	i = 1;
	while (i < var.nb + 1)
	{
		sem_wait(var.sem_die);
		i++;
	}
	i = 1;
	while (i < var.nb + 1)
		kill(var.philo[i++].pid, SIGKILL);
	return (ft_clear(&var, var.nb));
}
