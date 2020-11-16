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

static int	ft_puiss_dix(int n)
{
	int result;

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

static void			ft_rec(node *n, int a, int k, int t)
{
	char		c;
	int	i;
	int	b;

	i = ft_puiss_dix(k);
	c = a / i + 48;
	n->mess[t - k] =  c;
	if (k != 0)
	{
		b = a % i;
		ft_rec(n, b, k - 1, t);
	}
}

void				ft_putnbr_mess(node *n, int a, int t)
{
	int			k;
	int	b;

	b = a;
	k = 0;
	while ((b % 10) != b)
	{
		b = b / 10;
		k++;
	}
	ft_rec(n, a, k, t);
}