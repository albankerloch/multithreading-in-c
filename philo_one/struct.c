/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akerloc- <akerloc-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/09 16:40:22 by akerloc-          #+#    #+#             */
/*   Updated: 2019/10/10 17:52:08 by akerloc-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

int			ft_clear_mutex(t_bin *var, int i)
{
	int j;

	j = 1;
	while (j < i + 1)
	{
		pthread_mutex_destroy(&(var->philo[i].lock));
		j++;
	}
	pthread_mutex_destroy(&(var->lock_die));
	pthread_mutex_destroy(&(var->lock_crea));
	pthread_mutex_destroy(&(var->lock_std));
	free(var->philo);
	return (1);
}

static int	ft_create_philo(t_bin *var)
{
	int i;

	i = 1;
	while (i < var->nb + 1)
	{
		if (i == var->nb)
			var->philo[i].next = &(var->philo[1]);
		else
			var->philo[i].next = &(var->philo[i + 1]);
		var->philo[i].value = i;
		var->philo[i].lock_s = &(var->lock_std);
		var->philo[i].lock_c = &(var->lock_crea);
		var->philo[i].lock_die = &(var->lock_die);
		var->philo[i].tt_die = var->time_to_die;
		var->philo[i].tt_eat = var->time_to_eat;
		var->philo[i].tt_sleep = var->time_to_sleep;
		var->philo[i].count_eat = 0;
		var->philo[i].nb_eat = var->nb_eat;
		var->philo[i].nb = var->nb;
		if (pthread_mutex_init(&(var->philo[i].lock), NULL) != 0)
			return ((!(ft_clear_mutex(var, i))));
		i++;
	}
	return (1);
}

int			ft_create(t_bin *var)
{
	if (pthread_mutex_init(&(var->lock_std), NULL) != 0)
		return (0);
	if (pthread_mutex_init(&(var->lock_crea), NULL) != 0)
	{
		pthread_mutex_destroy(&(var->lock_std));
		return (0);
	}
	if (pthread_mutex_init(&(var->lock_die), NULL) != 0)
	{
		pthread_mutex_destroy(&(var->lock_crea));
		pthread_mutex_destroy(&(var->lock_std));
		return (0);
	}
	if (!(var->philo = malloc((var->nb + 1) * sizeof(t_node))))
	{
		pthread_mutex_destroy(&(var->lock_die));
		pthread_mutex_destroy(&(var->lock_crea));
		pthread_mutex_destroy(&(var->lock_std));
		return (0);
	}
	if (!(ft_create_philo(var)))
		return (0);
	return (1);
}
