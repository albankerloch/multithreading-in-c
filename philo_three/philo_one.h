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
#include <sys/types.h>
#include <sys/wait.h>


struct s_bin;

typedef struct s_node
{
    int value;
    int  tt_die;
    int  tt_eat;
    int  tt_sleep;
    long long start;
    int  count_eat;
    int  nb_eat;
    int fork_lock;
    struct s_node *next;
    int nb;
    sem_t *sem_die;
    char str[50];
    struct s_bin *var;
} node;

typedef struct s_test
{
    int value;
    int time_to_die;
    int time_to_eat;
    int time_to_sleep;
    int nb_eat;
    int nb;
    //sem_t *sem_die;
    //sem_t *sem_fork;
    //char str_die[2];
    //char str_fork[2];
} test;


typedef struct s_bin
{
    int time_to_die;
    int time_to_eat;
    int time_to_sleep;
    int nb_eat;
    int nb;
    node *philo;
    sem_t *sem_die;
    sem_t *sem_fork;
    char str_die[2];
    char str_fork[2];
} bin;

size_t			ft_strlen(const char *str);
void			ft_putstr_fd(char *s, int fd);
void			ft_putlnbr_fd(long long n, int fd);
void			ft_putnbr_fd(int n, int fd);
int				ft_isdigit(int i);
int				ft_atoi(const char *str);
int             ft_arg(bin *var, int ac, char **av);
int             ft_create(bin *var);
int             ft_clear(bin *var, int i);
void			*fn_philo(void *p_data);
void			*fn_monitor_eat(void *p_data);
void			*fn_monitor(void *p_data);
long long		current_timestamp(void);
void            print_value(sem_t *sem_die, int *val);
void			ft_putlnbr_str(long long a,  node *n);
void		    ft_putnbr_str(int a, node *n);
void		    ft_message(node *n, char *str, long long tm, unsigned int j);
#endif
