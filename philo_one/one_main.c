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
    usleep(50000);/*
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
        usleep(500000);
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
        usleep(500000);
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
  
  node n[3];
  //pthread_t thread_philo[3];
  //pthread_t thread_die[3];
  //pthread_mutex_t lock[3];
  
  n[1].next = &n[2];
  n[2].next = &n[1];
  
  
  if (ft_arg(&var, ac, av))
    return EXIT_FAILURE;
  if (ft_create(&var))
    return EXIT_FAILURE;  
  
  
  pthread_mutex_lock(&(var.lock_die));

  write(1, "Creation\n", 9);
  i = 1;
  while (i < var.nb + 1)
  {
   t = &n[i];
   if (pthread_mutex_init(&(n[i].lock), NULL) != 0)
     return EXIT_FAILURE;
   n[i].value = i;
   n[i].lock_s = &(var.lock_std);
   n[i].lock_die = &(var.lock_die);
   n[i].tt_die = var.time_to_die;
   n[i].tt_eat = var.time_to_eat;
   n[i].tt_sleep = var.time_to_sleep;
   n[i].count_eat = 0;
   n[i].nb_eat = var.nb_eat;
   if(pthread_create(&(n[i].thread), NULL, fn_philo, t))
     return EXIT_FAILURE;
   pthread_detach(n[i].thread);
   i++;
   /*
   t = &(var.philo[i]);
   if(pthread_create(var.philo[i].thread, NULL, fn_philo, t))
     return EXIT_FAILURE;
   pthread_detach(var.philo[i].thread);
   i++;
   */
  }
  pthread_mutex_lock(&(var.lock_die));
  pthread_mutex_unlock(&(var.lock_die));
  i = 1;
  while (i < var.nb + 1)
  {
    pthread_mutex_destroy(&(n[i].lock));
    i++;
  }
  pthread_mutex_destroy(&(var.lock_std));
  pthread_mutex_destroy(&(var.lock_die));
  free(var.philo);
  return EXIT_SUCCESS;
}
