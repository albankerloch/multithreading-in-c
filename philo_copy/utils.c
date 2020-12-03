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
