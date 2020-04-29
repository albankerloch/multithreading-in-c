#include "philo_one.h"

long long current_timestamp()
{
    struct timeval te; 
    gettimeofday(&te, NULL);
    long long milliseconds = te.tv_sec*1000LL + te.tv_usec/1000;
    return milliseconds;
}

static void * fn_philo (void * p_data)
{
  node *n;

  n = p_data;
  n->start = current_timestamp();

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
      if (pthread_mutex_lock(n->lock) != 0)
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
      if (pthread_mutex_lock(n->next->lock) != 0)
      {
        pthread_mutex_unlock(n->lock);
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

    pthread_mutex_unlock(n->next->lock);
    pthread_mutex_unlock(n->lock);

    if (n->count_eat == n->nb_eat)
      return NULL;

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
  pthread_t thread_philo[3];
  pthread_mutex_t lock[3];
  pthread_mutex_t lock_std;
  int time_to_die;
  int time_to_eat;
  int time_to_sleep;
  int i;
  int nb_eat;
  node n[3];
  void *t;
  
  (void)ac;
  (void)av;
  time_to_die = 100;
  time_to_eat = 500000;
  time_to_sleep = 1000000;
  nb_eat = 5;

  n[1].next = &n[2];
  n[2].next = &n[1];

  if (pthread_mutex_init(&lock_std, NULL) != 0)
     return EXIT_FAILURE;

  write(1, "Creation\n", 9);
  i = 1;
  while (i < 3)
  {
   t = &n[i];
   if (pthread_mutex_init(&lock[i], NULL) != 0)
     return EXIT_FAILURE;
   n[i].value = i;
   n[i].lock = &lock[i];
   n[i].lock_s = &lock_std;
   n[i].tt_die = time_to_die;
   n[i].tt_eat = time_to_eat;
   n[i].tt_sleep = time_to_sleep;
   n[i].count_eat = 0;
   n[i].nb_eat = nb_eat;
   n[i].thread = &thread_philo[i];
   if(pthread_create(&thread_philo[i], NULL, fn_philo, t))
     return EXIT_FAILURE;
   i++;
  }
  i = 1;
  while (i < 3)
  {
    pthread_join(thread_philo[i], NULL);
    i++;
  }
  i = 1;
  while (i < 3)
  {
    pthread_mutex_destroy(&lock[i]);
    i++;
  }
  pthread_mutex_destroy(&lock_std);
  return EXIT_SUCCESS;
}
