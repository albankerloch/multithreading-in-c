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

int			ft_arg(t_bin *var, int ac, char **av)
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
	if (ft_create(var))
	{
		write(2, "Memory allocation error\n",\
ft_strlen("Memory allocation error\n"));
		return (0);
	}
	return (1);
}

static int	ft_loop(int i, t_bin *var)
{
	var->philo[i].pid = fork();
	if (var->philo[i].pid < 0)
	{
		write(2, "Fork error\n", ft_strlen("Fork error\n"));
		return (0);
	}
	else if (var->philo[i].pid == 0)
	{
		ft_routine(&var->philo[i]);
		exit(0);
	}
	usleep(10);
	return (1);
}

int			main(int ac, char **av)
{
	int		i;
	t_bin	var;

	if (!(ft_arg(&var, ac, av)))
		return (1);
	i = 1;
	while (i < var.nb + 1)
	{
		if (!(ft_loop(i, &var)))
			return (ft_clear(&var));
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
	return (ft_clear(&var));
}
