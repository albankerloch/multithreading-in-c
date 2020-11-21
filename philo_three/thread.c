/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akerloc- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/08 19:55:49 by akerloc-          #+#    #+#             */
/*   Updated: 2019/10/07 16:39:58 by akerloc-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_three.h"

void		ft_chg_str(t_node *n, char *str, unsigned int t, unsigned int j)
{
	unsigned int i;
	
	i = 0;
	while (i < j)
	{
		n->str[i + t] = str[i];
		i++;
	}
	n->str[i + t ] = '\n';
	n->str[i + t + 1] = '\0';
}

void		ft_message(t_node *n, char *str, long long tm, unsigned int j)
{
	unsigned int t;

	ft_putlnbr_str(tm, n);
	n->str[13] = ' ';
	ft_putnbr_str(n->value, n);
	t = ft_strlen(n->str);
	n->str[t] = ' ';
	ft_chg_str(n, str, t, j);
	write(1, n->str, ft_strlen(n->str));
}

void	ft_activity(t_node *n)
{
	ft_message(n, " has taken a fork\n", current_timestamp(), 17);
	ft_message(n, " has taken a fork\n", current_timestamp(), 17);
	n->start = current_timestamp();
	n->count_eat = n->count_eat + 1;
	ft_message(n, " is eating\n", n->start, 10);
	usleep(n->tt_eat * 1000);
	sem_post(n->var->sem_fork);
	sem_post(n->var->sem_fork);
	if (n->count_eat == n->nb_eat)
	{
		sem_post(n->sem_die);
		exit(1);
	}
	ft_message(n, " is sleeping\n", current_timestamp(), 12);
	usleep(n->tt_sleep * 1000);
	ft_message(n, " is thinking\n", current_timestamp(), 12);
}