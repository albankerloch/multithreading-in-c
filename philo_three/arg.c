#include "philo_one.h"

int			ft_arg(bin *var, int ac, char **av)
{
	if (ac > 6 || ac < 5)
		return (1);
	var->nb = ft_atoi(av[1]);
	var->time_to_die = ft_atoi(av[2]);
	var->time_to_eat = ft_atoi(av[3]);
	var->time_to_sleep = ft_atoi(av[4]);
	var->nb_eat = ac == 6 ? ft_atoi(av[5]) : -1;
	return (0);
}

int			ft_clear(bin *var, int i)
{
	i = 1;
	i++;
	free(var->philo);
	return (0);
}

static int	ft_create_philo(bin *var)
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

int			ft_create(bin *var)
{
	if (!(var->philo = malloc((var->nb + 1) * sizeof(node))))
		return (1);
	if (ft_create_philo(var))
		return (1);
	return (0);
}
