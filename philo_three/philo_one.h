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


typedef struct s_bin
{
    int time_to_die;
    int time_to_eat;
    int time_to_sleep;
    int nb_eat;
    int nb;
    int count_eat;
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
void			ft_putlnbr_str(long long a, char str[50]);
void		    ft_putnbr_str(int a, char str[50]);
void		    ft_message(int i, char *str_txt, long long tm, unsigned int j, char str[50]);
void	        ft_activity(int i, char str[50], long long *start, bin *var, sem_t *sem_fork);

#endif
