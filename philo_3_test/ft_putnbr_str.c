/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_str.c                                    :+:      :+:    :+:   */
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

static void	ft_rec(int a, int p, node *n, int t)
{
	char	c;
	int		i;
	int		b;

	i = ft_puiss_dix(p);
	c = a / i + 48;
	n->str[t] = c;
	if (p != 0)
	{
		b = a % i;
		ft_rec(b, p - 1, n, t + 1);
	}
}

void		ft_putnbr_str(int a, node *n)
{
	int p;
	int b;

	b = a;
	p = 0;
	while ((b % 10) != b)
	{
		b = b / 10;
		p++;
	}
	ft_rec(a, p, n, 14);
	n->str[p + 15] = '\0';
}