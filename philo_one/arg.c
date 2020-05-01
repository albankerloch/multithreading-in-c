#include "philo_one.h"

int ft_arg(bin *var, int ac, char **av)
{
    if (ac > 6 || ac < 5)
        return (1);
    var->nb = ft_atoi(av[1]);
    var->time_to_sleep = ft_atoi(av[2]);
    var->time_to_die = ft_atoi(av[3]);
    var->time_to_eat = ft_atoi(av[4]);
    var->nb_eat = ac == 6 ? ft_atoi(av[5]) : - 1;
    return (0);   
}