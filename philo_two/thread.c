/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread.c                                           :+:      :+:    :+:   */
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
	t_node	*n;
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
	t_node *n;

	n = p_data;
	while (1)
	{
		usleep(2000);
		if (current_timestamp() - n->start > n->tt_die && \
n->count_eat != n->nb_eat)
		{
			ft_message_die(n, " died\n", n->start, 5);
			sem_post(n->sem_die);
			break ;
		}
	}
	return (0);
}

static void	ft_activity(t_node *n)
{
	ft_message(n, " has taken a fork\n", current_timestamp(), 17);
	ft_message(n, " has taken a fork\n", current_timestamp(), 17);
	n->start = current_timestamp();
	n->count_eat = n->count_eat + 1;
	ft_message(n, " is eating\n", n->start, 10);
	ft_sleep(n->tt_eat);
	sem_post(n->var->sem_fork);
	sem_post(n->var->sem_fork);
	if (n->count_eat == n->nb_eat)
		while (1)
		{
			usleep(5000 * 1000);
		}
	ft_message(n, " is sleeping\n", current_timestamp(), 12);
	ft_sleep(n->tt_sleep);
	ft_message(n, " is thinking\n", current_timestamp(), 12);
}

void		*fn_philo(void *p_data)
{
	t_node *n;

	n = p_data;
	n->start = current_timestamp();
	if (pthread_create(&(n->monitor_die), NULL, fn_monitor, p_data))
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
