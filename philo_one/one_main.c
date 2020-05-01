#include "philo_one.h"

long long current_timestamp()
{
    struct timeval te; 
    gettimeofday(&te, NULL);
    long long milliseconds = te.tv_sec*1000LL + te.tv_usec/1000;
    return milliseconds;
}


static void * fn_monitor (void * p_data)
{
  node *n;

  n = p_data;
  //ft_putlnbr_fd(n->start, 1);
  while (1)
  {
    usleep(10);/*
    pthread_mutex_lock(n->lock_s);
    ft_putlnbr_fd(current_timestamp(), 1);
    write(1," ", 1);
    ft_putlnbr_fd(n->start, 1);
    write(1," ", 1);
    ft_putnbr_fd(n->value, 1);
    write(1, " has test\n", 10);
    pthread_mutex_unlock(n->lock_s);*/
    if (current_timestamp() - n->start > n->tt_die)
    {
      pthread_mutex_lock(n->lock_s);
      ft_putlnbr_fd(current_timestamp(), 1);
      write(1," ", 1);
      ft_putlnbr_fd(n->start, 1);
      write(1," ", 1);
      ft_putnbr_fd(n->value, 1);
      write(1, " has died\n", 10);
      pthread_mutex_unlock(n->lock_s);
      pthread_mutex_unlock(n->lock_die);
      return NULL;
    }
  }
  return NULL;
}

static void * fn_philo (void * p_data)
{
  node *n;

  n = p_data;
  n->start = current_timestamp();

  if(pthread_create(&(n->monitor_die), NULL, fn_monitor, p_data))
    return NULL;
  pthread_detach(n->monitor_die);

  pthread_mutex_lock(n->lock_s);

  ft_putlnbr_fd(n->start, 1);
  write(1," ", 1);
  ft_putnbr_fd(n->value, 1);
  write(1, " is thinking\n", 14);

  pthread_mutex_unlock(n->lock_s);

  while (1)
  {
    while (1)
    {
      if (pthread_mutex_lock(&(n->lock)) != 0)
      {
        usleep(20);
        continue;
      }
      pthread_mutex_lock(n->lock_s);
      ft_putlnbr_fd(current_timestamp(), 1);
      write(1," ", 1);
      ft_putnbr_fd(n->value, 1);
      ft_putnbr_fd(n->value, 1);
      write(1, " has taken a fork\n", 18);
      pthread_mutex_unlock(n->lock_s);
      if (pthread_mutex_lock(&(n->next->lock)) != 0)
      {
        pthread_mutex_unlock(&(n->lock));
        usleep(20);
        continue;
      }
      pthread_mutex_lock(n->lock_s);
      ft_putlnbr_fd(current_timestamp(), 1);
      write(1," ", 1);
      ft_putnbr_fd(n->value, 1);
      ft_putnbr_fd(n->next->value, 1);
      write(1, " has taken a fork\n", 18);
      pthread_mutex_unlock(n->lock_s);
      break;
    }
    
    n->start = current_timestamp();
    n->count_eat = n->count_eat + 1;

    pthread_mutex_lock(n->lock_s);
    
    ft_putlnbr_fd(n->start, 1);
    write(1," ", 1);
    ft_putnbr_fd(n->value, 1);
    ft_putnbr_fd(n->count_eat, 1);
    write(1, " is eating\n", 11);

    pthread_mutex_unlock(n->lock_s);

    usleep(n->tt_eat);

    pthread_mutex_unlock(&(n->next->lock));
    pthread_mutex_unlock(&(n->lock));

    if (n->count_eat == n->nb_eat)
    {
      //pthread_mutex_unlock(n->lock_die);
      return NULL;
    }
      
    pthread_mutex_lock(n->lock_s);
    
    ft_putlnbr_fd(current_timestamp(), 1);
    write(1," ", 1);
    ft_putnbr_fd(n->value, 1);
    write(1, " is sleeping\n", 13);

    pthread_mutex_unlock(n->lock_s);

    usleep(n->tt_sleep);

    pthread_mutex_lock(n->lock_s);

    ft_putlnbr_fd(current_timestamp(), 1);
    write(1," ", 1);
    ft_putnbr_fd(n->value, 1);
    write(1, " is thinking\n", 14);

    pthread_mutex_unlock(n->lock_s);
  }
  return NULL;
}
 
int main (int ac, char **av)
{
  int i;
  bin var;
  void *t;
      
  if (ft_arg(&var, ac, av))
    return (1);
  if (ft_create(&var))
    return (1);
  pthread_mutex_lock(&(var.lock_die));
  i = 1;
  while (i < var.nb + 1)
  {
   t = &(var.philo[i]);
   if(pthread_create(&(var.philo[i].thread), NULL, fn_philo, t))
     return (ft_clear_mutex(&var, var.nb));
   pthread_detach(var.philo[i].thread);
   i++;
  }
  pthread_mutex_lock(&(var.lock_die));
  pthread_mutex_unlock(&(var.lock_die));
  ft_clear_mutex(&var, var.nb);
  return (0);
}
