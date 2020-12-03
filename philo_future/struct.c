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

#include "philo_two.h"

int			ft_clear(t_bin *var, int i, int l)
{
	int j;

	(void)l;
	j = 1;
	while (j < i + 1)
	{
		sem_close(var->philo[j].sem_eat);
		sem_unlink(var->philo[j].str_eat);
		j++;
	}
	sem_close(var->sem_fork);
	sem_unlink(var->str_fork);
	sem_close(var->sem_std);
	sem_unlink(var->str_std);
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
		var->philo[i].str[0] = '\0';
		var->philo[i].var = var;
		var->philo[i].sem_std = var->sem_std;
		ft_putnbr_str_eat(i, &(var->philo[i]));
		sem_unlink(var->philo[i].str_eat);
		if (!(var->philo[i].sem_eat =\
sem_open(var->philo[i].str_eat, O_CREAT | O_EXCL, 0664, 1)))
			return ((!(ft_clear(var, i, 1))));
		i++;
	}
	return (0);
}

int			ft_create(t_bin *var)
{
	var->str_fork[0] = 'f';
	var->str_fork[1] = '\0';
	sem_unlink(var->str_fork);
	if (!(var->sem_fork =\
sem_open(var->str_fork, O_CREAT | O_EXCL, 0664, var->nb)))
		return (1);
	var->str_std[0] = 's';
	var->str_std[1] = '\0';
	sem_unlink(var->str_std);
	if (!(var->sem_std = sem_open(var->str_std, O_CREAT | O_EXCL, 0664, 1)))
	{
		sem_close(var->sem_fork);
		sem_unlink(var->str_fork);
		return (1);
	}
	if (!(var->philo = malloc((var->nb + 1) * sizeof(t_node))))
	{
		sem_close(var->sem_fork);
		sem_unlink(var->str_fork);
		sem_close(var->sem_std);
		sem_unlink(var->str_std);
		return (1);
	}
	if (ft_create_philo(var, 1))
		return (1);
	return (0);
}
