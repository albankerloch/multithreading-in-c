/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akerloc- <akerloc-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/09 16:40:22 by akerloc-          #+#    #+#             */
/*   Updated: 2019/10/10 17:52:08 by akerloc-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

static long long	ft_puiss_dix(int n)
{
	long long result;

	if (n == 0)
	{
		result = 1;
	}
	else
	{
		result = 10 * ft_puiss_dix(n - 1);
	}
	return (result);
}

static void			ft_rec(long long a, int n, int fd)
{
	char		c;
	long long	i;
	long long	b;

	i = ft_puiss_dix(n);
	c = a / i + 48;
	write(fd, &c, 1);
	if (n != 0)
	{
		b = a % i;
		ft_rec(b, n - 1, fd);
	}
}

void				ft_putlnbr_fd(long long a, int fd)
{
	int			n;
	long long	b;

	if (a < 0)
	{
		write(fd, "-", 1);
		a = -a;
	}
	b = a;
	n = 0;
	while ((b % 10) != b)
	{
		b = b / 10;
		n++;
	}
	ft_rec(a, n, fd);
}
