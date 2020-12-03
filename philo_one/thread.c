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

#include "philo_one.h"

void		*fn_monitor(void *p_data)
{
	t_node *n;

	n = p_data;
	while (!(n->var->end) && !(n->end))
	{
		usleep(2000);
		if (n->var->count_eat == n->var->nb * n->var->nb_eat)
		{
			n->var->end = 1;
			return (0);
		}
		if (current_timestamp() - n->start > n->tt_die && !(n->end))
		{
			if (!(n->var->end))
				ft_message_die(n, " died\n", current_timestamp(), 5);
			n->var->end = 1;
			pthread_mutex_unlock(n->lock_die);
			return (0);
		}
	}
	return (0);
}

static int	ft_activity(t_node *n)
{
	pthread_mutex_lock(&(n->lock));
	ft_message(n, " has taken a fork\n", current_timestamp(), 17);
	pthread_mutex_lock(&(n->next->lock));
	ft_message(n, " has taken a fork\n", current_timestamp(), 17);
	n->start = current_timestamp();
	ft_message(n, " is eating\n", n->start, 10);
	if (!(n->var->end))
		ft_sleep(n->tt_eat);
	pthread_mutex_unlock(&(n->next->lock));
	pthread_mutex_unlock(&(n->lock));
	if (!(n->var->end))
	{
		n->count_eat = n->count_eat + 1;
		n->var->count_eat = n->var->count_eat + 1;
		if (n->count_eat > n->var->nb_eat && n->var->nb_eat >= 0)
		{
			n->end = 1;
			return (0);
		}
	}
	ft_message(n, " is sleeping\n", current_timestamp(), 12);
	ft_sleep(n->tt_sleep);
	ft_message(n, " is thinking\n", current_timestamp(), 12);
	return (1);
}

void		*fn_philo(void *p_data)
{
	t_node *n;

	n = p_data;
	n->start = current_timestamp();
	ft_message(n, " is thinking\n", n->start, 12);
	while (!(n->var->end))
	{
		if(!(ft_activity(n)))
			return (0);
	}
	return (0);
}
