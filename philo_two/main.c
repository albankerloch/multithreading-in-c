/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akerloc- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/07 17:31:51 by akerloc-          #+#    #+#             */
/*   Updated: 2019/10/07 17:41:11 by akerloc-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_two.h"

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
			ft_message(n, " died\n", n->start, 5);
			sem_post(n->sem_die);
			break ;
		}
	}
	return (0);
}

int	ft_arg(bin *var, int ac, char **av)
{
	if (ac > 6 || ac < 5 || (!ft_check_arg(ac, av)))
	{
		write(2, "Argument error\n", ft_strlen("Argument error\n"));
		return (0);
	}
	var->nb = ft_atoi(av[1]);
	var->time_to_die = ft_atoi(av[2]);
	var->time_to_eat = ft_atoi(av[3]);
	var->time_to_sleep = ft_atoi(av[4]);
	var->nb_eat = ac == 6 ? ft_atoi(av[5]) : -1;
	return (1);
}

int			main(int ac, char **av)
{
	int		i;
	bin		var;
	void	*t;

	if (!(ft_arg(&var, ac, av)))
		return (1);
	var.str_fork[0] = 'f';
	var.str_fork[1] = '\0';
	sem_unlink(var.str_fork);
	var.sem_fork = sem_open(var.str_fork, O_CREAT | O_EXCL, 0664, var.nb);
	var.str_die[0] = 'd';
	var.str_die[1] = '\0';
	sem_unlink(var.str_die);
	var.sem_die = sem_open(var.str_die, O_CREAT | O_EXCL, 0664, 1);
	sem_wait(var.sem_die);
	if (ft_create(&var))
	{
		write(2, "Memory allocation error\n",\
ft_strlen("Memory allocation error\n"));
		return (1);
	}
	i = 1;
	while (i < var.nb + 1)
	{
		t = &(var.philo[i]);
		if (pthread_create(&(var.philo[i].thread), NULL, fn_philo, t))
			return (ft_clear(&var, var.nb));
		pthread_detach(var.philo[i].thread);
		i++;
	}
	t = &(var.philo[1]);
	if (pthread_create(&(var.philo[1].thread), NULL, fn_monitor_eat, t))
		return (ft_clear(&var, var.nb));
	pthread_detach(var.philo[i].thread);
	sem_wait(var.sem_die);
	return (ft_clear(&var, var.nb));
}
