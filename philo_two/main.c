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

int	ft_arg(t_bin *var, int ac, char **av)
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

int	main(int ac, char **av)
{
	int		i;
	t_bin	var;
	void	*t;

	if (!(ft_arg(&var, ac, av)))
		return (1);
	i = 1;
	while (i < var.nb + 1)
	{
		t = &(var.philo[i]);
		if (pthread_create(&(var.philo[i].thread), NULL, fn_philo, t))
			return (ft_clear(&var));
		pthread_detach(var.philo[i].thread);
		usleep(10);
		i++;
	}
	t = &(var.philo[1]);
	if (pthread_create(&(var.philo[1].thread), NULL, fn_monitor_eat, t))
		return (ft_clear(&var));
	pthread_detach(var.philo[i].thread);
	sem_wait(var.sem_die);
	return (ft_clear(&var));
}
