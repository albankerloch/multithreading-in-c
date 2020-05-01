#ifndef PHILO_ONE_H
# define PHILO_ONE_H

# include <stdio.h>
# include <stdlib.h>
# include <pthread.h>
# include <string.h> 
# include <unistd.h>
# include <sys/time.h>

typedef struct s_node
{
    int value;
    pthread_mutex_t *lock_s;
    pthread_mutex_t lock;
    pthread_mutex_t *lock_die;
    int  tt_die;
    int  tt_eat;
    int  tt_sleep;
    long long start;
    int  count_eat;
    int  nb_eat;
    pthread_t thread;
    pthread_t monitor_die;
    struct s_node *next;
} node;

typedef struct s_bin
{
    int time_to_die;
    int time_to_eat;
    int time_to_sleep;
    int nb_eat;
    int nb;
    pthread_mutex_t lock_std;
    pthread_mutex_t lock_die;
    node *philo;
} bin;

size_t			ft_strlen(const char *str);
void			ft_putstr_fd(char *s, int fd);
void			ft_putlnbr_fd(long long n, int fd);
void			ft_putnbr_fd(int n, int fd);
int				ft_isdigit(int i);
int				ft_atoi(const char *str);
int             ft_arg(bin *var, int ac, char **av);
int             ft_create(bin *var);

#endif
