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

#include "philo_one.h"

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

void		ft_message(node *n, char *str, long long tm)
{
	int i;
	int k;
	int b;

	pthread_mutex_lock(n->lock_s);
	ft_putlnbr_mess(n, tm, 12);
	n->mess[13] = ' ';
	b = n->value;
	k = 0;
	while ((b % 10) != b)
	{
		b = b / 10;
		k++;
	}
	b = n->value;
	ft_putlnbr_mess(n, n->value, 14 + k);
	i = 0;
	while (str[i])
	{
		n->mess[i + 15 + k] = str[i];
		i++;
	}
	n->mess[i + 15 + k] = '\0';
	write(1, n->mess, ft_strlen(n->mess));
	pthread_mutex_unlock(n->lock_s);
}

void		ft_sleep(int n)
{
	time_t start;

	start = current_timestamp();
	while ((current_timestamp() - start) < n)
		usleep(200);
}

long long	current_timestamp(void)
{
	struct timeval	te;
	long long		m;

	gettimeofday(&te, NULL);
	m = te.tv_sec * 1000LL + te.tv_usec / 1000;
	return (m);
}
