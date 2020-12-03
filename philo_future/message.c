/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   message.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akerloc- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/07 17:31:51 by akerloc-          #+#    #+#             */
/*   Updated: 2019/10/07 17:41:11 by akerloc-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_two.h"

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

void		ft_message(t_node *n, char *str, long long tm, unsigned int j)
{
	unsigned int t;

	pthread_mutex_lock(n->lock_std);
	ft_putlnbr_str(tm, n);
	n->str[13] = ' ';
	ft_putnbr_str(n->value, n);
	t = ft_strlen(n->str);
	n->str[t] = ' ';
	ft_chg_str(n, str, t, j);
	if (!(n->var->end))
		write(1, n->str, ft_strlen(n->str));
	pthread_mutex_unlock(n->lock_std);
}

void		ft_message_die(t_node *n, char *str, long long tm, unsigned int j)
{
	unsigned int t;

	ft_putlnbr_str(tm, n);
	n->str[13] = ' ';
	ft_putnbr_str(n->value, n);
	t = ft_strlen(n->str);
	n->str[t] = ' ';
	ft_chg_str(n, str, t, j);
	if (!(n->var->end))
		write(1, n->str, ft_strlen(n->str));
}
