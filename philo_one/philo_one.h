/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_one.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akerloc- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/07 17:31:51 by akerloc-          #+#    #+#             */
/*   Updated: 2019/10/07 17:41:11 by akerloc-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_ONE_H
# define PHILO_ONE_H

# include <stdio.h>
# include <stdlib.h>
# include <pthread.h>
# include <string.h>
# include <unistd.h>
# include <sys/time.h>

typedef struct		s_node
{
	int				value;
	pthread_mutex_t	*lock_s;
	pthread_mutex_t	*lock_c;
	pthread_mutex_t	lock;
	pthread_mutex_t	*lock_die;
	int				tt_die;
	int				tt_eat;
	int				tt_sleep;
	long long		start;
	int				count_eat;
	int				nb_eat;
	pthread_t		thread;
	pthread_t		monitor_die;
	struct s_node	*next;
	char			mess[50];
	int				nb;
}					t_node;

typedef struct		s_bin
{
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				nb_eat;
	int				nb;
	pthread_mutex_t	lock_std;
	pthread_mutex_t	lock_crea;
	pthread_mutex_t	lock_die;
	t_node			*philo;
}					t_bin;

size_t				ft_strlen(const char *str);
void				ft_putlnbr_mess(t_node *n, long long a, int t);
int					ft_strisdigit(char *str);
int					ft_check_arg(int ac, char **av);
int					ft_atoi(const char *str);
int					ft_arg(t_bin *var, int ac, char **av);
int					ft_create(t_bin *var);
int					ft_clear_mutex(t_bin *var, int i);
void				*fn_philo(void *p_data);
void				*fn_monitor_eat(void *p_data);
void				*fn_monitor(void *p_data);
long long			current_timestamp(void);
void				ft_message(t_node *n, char *str, long long tm);
void				ft_sleep(int n);

#endif
