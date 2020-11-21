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

#include "philo_one.h"

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
	if (!(ft_create(var)))
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
	bin		var;
	void	*t;

	if (!(ft_arg(&var, ac, av)))
		return (1);
	pthread_mutex_lock(&(var.lock_die));
	i = 1;
	while (i < var.nb + 1)
	{
		t = &(var.philo[i]);
		pthread_mutex_lock(&(var.lock_crea));
		if (pthread_create(&(var.philo[i].thread), NULL, fn_philo, t))
			return (ft_clear_mutex(&var, var.nb));
		pthread_detach(var.philo[i].thread);
		pthread_mutex_lock(&(var.lock_crea));
		pthread_mutex_unlock(&(var.lock_crea));
		i++;
	}
	if (pthread_create(&(var.philo[i].thread), NULL, fn_monitor_eat, t))
		return (ft_clear_mutex(&var, var.nb));
	pthread_detach(var.philo[i].thread);
	pthread_mutex_lock(&(var.lock_die));
	pthread_mutex_unlock(&(var.lock_die));
	return (ft_clear_mutex(&var, var.nb));
}
