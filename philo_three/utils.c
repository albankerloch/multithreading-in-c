/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akerloc- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/07 17:31:51 by akerloc-          #+#    #+#             */
/*   Updated: 2019/10/07 17:41:11 by akerloc-         ###   ########.fr       */
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
	n->str[i + t] = '\n';
	n->str[i + t + 1] = '\0';
}

void		ft_message_die(t_node *n, char *str, long long tm, unsigned int j)
{
	unsigned int t;

	sem_wait(n->sem_std);
	ft_putlnbr_str(tm, n);
	n->str[13] = ' ';
	ft_putnbr_str(n->value, n);
	t = ft_strlen(n->str);
	n->str[t] = ' ';
	ft_chg_str(n, str, t, j);
	write(1, n->str, ft_strlen(n->str));
}

void		ft_message(t_node *n, char *str, long long tm, unsigned int j)
{
	unsigned int t;

	sem_wait(n->sem_std);
	ft_putlnbr_str(tm, n);
	n->str[13] = ' ';
	ft_putnbr_str(n->value, n);
	t = ft_strlen(n->str);
	n->str[t] = ' ';
	ft_chg_str(n, str, t, j);
	write(1, n->str, ft_strlen(n->str));
	sem_post(n->sem_std);
}

int			ft_check_arg(int ac, char **av)
{
	int i;

	i = 1;
	while (i < ac)
	{
		if (!(ft_strisdigit(av[i])))
			return (0);
		i++;
	}
	return (1);
}

int			ft_strisdigit(char *str)
{
	int i;

	i = 0;
	while (str[i])
	{
		if (!(str[i] >= 48 && str[i] <= 57))
			return (0);
		i++;
	}
	return (1);
}

long long	current_timestamp(void)
{
	struct timeval	te;
	long long		m;

	gettimeofday(&te, NULL);
	m = te.tv_sec * 1000LL + te.tv_usec / 1000;
	return (m);
}
