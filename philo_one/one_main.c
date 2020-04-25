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
  (void) p_data;
  ft_putnbr_fd(current_timestamp(), 1);
  write(1, "1 is thinking\n", 15);
  //  pthread_mutex_lock(&lock1);
  return NULL;
}
 
int main (int ac, char **av)
{
   pthread_t thread_philo;
   pthread_mutex_t lock1;
   pthread_mutex_t lock2;

   (void)ac;
   (void)av;
   
   write(1, "Creation\n", 9);
   if (pthread_mutex_init(&lock1, NULL) != 0)
       return EXIT_FAILURE;
   if (pthread_mutex_init(&lock2, NULL) != 0)
       return EXIT_FAILURE;
   if(pthread_create(&thread_philo, NULL, fn_philo, NULL))
       return EXIT_FAILURE;
   pthread_join (thread_philo, NULL);
   pthread_mutex_destroy(&lock1);
   pthread_mutex_destroy(&lock2);
   return EXIT_SUCCESS;
}
