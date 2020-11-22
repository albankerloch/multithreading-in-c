/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_one.c                                        :+:      :+:    :+:   */
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
# include <semaphore.h>
# include <fcntl.h>
# include <sys/stat.h>

struct s_bin;

typedef struct		s_node
{
	int				value;
	pthread_mutex_t	*lock_die;
	pthread_mutex_t	*lock_std;
	pthread_mutex_t	lock;
	int				tt_die;
	int				tt_eat;
	int				tt_sleep;
	long long		start;
	int				count_eat;
	int				nb_eat;
	pthread_t		thread;
	pthread_t		monitor_die;
	int				fork_lock;
	struct s_node	*next;
	int				nb;
	char			str[50];
	struct s_bin	*var;
}					t_node;

typedef struct		s_bin
{
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				nb_eat;
	int				nb;
	int				end;
	t_node			*philo;
	pthread_mutex_t	lock_die;
	pthread_mutex_t	lock_std;
	char			str_die[2];
	char			str_fork[2];
}					t_bin;

void				ft_sleep(int n);
size_t				ft_strlen(const char *str);
void				ft_putstr_fd(char *s, int fd);
void				ft_putlnbr_fd(long long n, int fd);
void				ft_putnbr_fd(int n, int fd);
int					ft_isdigit(int i);
int					ft_atoi(const char *str);
int					ft_arg(t_bin *var, int ac, char **av);
int					ft_create(t_bin *var);
int					ft_clear(t_bin *var, int i);
void				*fn_philo(void *p_data);
void				*fn_monitor_eat(void *p_data);
void				*fn_monitor(void *p_data);
long long			current_timestamp(void);
void				print_value(sem_t *sem_die, int *val);
void				ft_putlnbr_str(long long a, t_node *n);
void				ft_putnbr_str(int a, t_node *n);
void				ft_message(t_node *n, char *str, long long tm,\
unsigned int j);
int					ft_check_arg(int ac, char **av);
int					ft_strisdigit(char *str);
void				ft_message_die(t_node *n, char *str, long long tm, unsigned int j);

#endif
