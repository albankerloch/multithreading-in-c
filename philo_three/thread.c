/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akerloc- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/08 19:55:49 by akerloc-          #+#    #+#             */
/*   Updated: 2019/10/07 16:39:58 by akerloc-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_three.h"

void		*fn_monitor(void *p_data)
{
	t_node	*n;
	int		i;

	n = p_data;
	while (1)
	{
		usleep(10 * 000);
		if (current_timestamp() - n->start > n->tt_die && \
n->count_eat != n->nb_eat)
		{
			ft_message_die(n, " died\n", n->start, 5);
			i = 1;
			while (i < n->var->nb + 1)
			{
				sem_post(n->sem_die);
				i++;
			}
			break ;
		}
	}
	return (0);
}

int			ft_routine(t_node *n)
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

void		ft_activity(t_node *n)
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
	{
		sem_post(n->sem_die);
		exit(1);
	}
	ft_message(n, " is sleeping\n", current_timestamp(), 12);
	ft_sleep(n->tt_sleep);
	ft_message(n, " is thinking\n", current_timestamp(), 12);
}
