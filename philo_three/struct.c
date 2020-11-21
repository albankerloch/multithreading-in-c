/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akerloc- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/08 19:55:49 by akerloc-          #+#    #+#             */
/*   Updated: 2019/10/07 16:39:58 by akerloc-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_three.h"

int			ft_clear(t_bin *var, int i)
{
	i = 1;
	i++;
	free(var->philo);
	return (0);
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
		var->philo[i].tt_die = var->time_to_die;
		var->philo[i].tt_eat = var->time_to_eat;
		var->philo[i].tt_sleep = var->time_to_sleep;
		var->philo[i].count_eat = 0;
		var->philo[i].nb_eat = var->nb_eat;
		var->philo[i].fork_lock = 0;
		var->philo[i].nb = var->nb;
		var->philo[i].sem_die = var->sem_die;
		var->philo[i].str[0] = '\0';
		var->philo[i].var = var;
		i++;
	}
	return (0);
}

int			ft_create(t_bin *var)
{
	var->str_fork[0] = 'f';
	var->str_fork[1] = '\0';
	sem_unlink(var->str_fork);
	var->sem_fork = sem_open(var->str_fork, O_CREAT | O_EXCL, 0664, var->nb);
	var->str_die[0] = 'd';
	var->str_die[1] = '\0';
	sem_unlink(var->str_die);
	var->sem_die = sem_open(var->str_die, O_CREAT | O_EXCL, 0664, 1);
	if (!(var->philo = malloc((var->nb + 1) * sizeof(t_node))))
		return (1);
	if (ft_create_philo(var))
		return (1);
	return (0);
}
