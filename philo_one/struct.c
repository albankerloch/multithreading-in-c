/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akerloc- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/07 17:31:51 by akerloc-          #+#    #+#             */
/*   Updated: 2019/10/07 17:41:11 by akerloc-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

int			ft_clear(t_bin *var, int i)
{
	int j;

	j = 1;
	while (j < i + 1)
	{
		pthread_mutex_destroy(&(var->philo[i].lock));
		j++;
	}
	pthread_mutex_destroy(&(var->lock_die));
	pthread_mutex_destroy(&(var->lock_std));
	free(var->philo);
	return (1);
}

static int	ft_create_philo(t_bin *var, int i)
{
	while (i < var->nb + 1)
	{
		if (i == var->nb)
			var->philo[i].next = &(var->philo[1]);
		else
			var->philo[i].next = &(var->philo[i + 1]);
		var->philo[i].value = i;
		var->philo[i].tt_die = var->time_to_die;
		var->philo[i].tt_eat = var->time_to_eat;
		var->philo[i].tt_sleep = var->time_to_sleep;
		var->philo[i].count_eat = 0;
		var->philo[i].nb_eat = var->nb_eat;
		var->philo[i].fork_lock = 0;
		var->philo[i].nb = var->nb;
		var->philo[i].str[0] = '\0';
		var->philo[i].var = var;
		var->philo[i].lock_die = &(var->lock_die);
		var->philo[i].lock_std = &(var->lock_std);
		if (pthread_mutex_init(&(var->philo[i].lock), NULL) != 0)
			return ((!(ft_clear(var, i))));
		i++;
	}
	return (0);
}

int			ft_create(t_bin *var)
{
	if (pthread_mutex_init(&(var->lock_std), NULL) != 0)
		return (1);
	if (pthread_mutex_init(&(var->lock_die), NULL) != 0)
	{
		pthread_mutex_destroy(&(var->lock_std));
		return (1);
	}
	pthread_mutex_lock(&(var->lock_die));
	if (!(var->philo = malloc((var->nb + 1) * sizeof(t_node))))
	{
		pthread_mutex_destroy(&(var->lock_die));
		pthread_mutex_destroy(&(var->lock_std));
		return (1);
	}
	if (ft_create_philo(var, 1))
		return (1);
	return (0);
}
