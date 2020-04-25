#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h> 
#include <unistd.h>
#include <sys/time.h>

#define INITIAL_STOCK   20
#define NB_CLIENTS      5

long long current_timestamp()
{
    struct timeval te; 
    gettimeofday(&te, NULL);
    long long milliseconds = te.tv_sec*1000LL + te.tv_usec/1000;
    return milliseconds;
}

typedef struct
{
   int stock;
 
   pthread_t thread_store;
   pthread_t thread_clients [NB_CLIENTS];
 
   pthread_mutex_t mutex_stock;
}
philo_t;
 
static void * fn_philo (void * p_data)
{
  printf ("Remplissage du stock d'articles !\n");
  return NULL;
}
 
int main (int ac, char **av)
{
   int ret;
   void *t;
   pthread_t thread_philo;

   (void)ac;
   (void)av;
   
   ret = 0;
   write(1, "Creation\n", 9);
   ret = pthread_create(&thread_philo, NULL, fn_philo, NULL);
 
   if (!ret)
   {
     printf("%lld \n", current_timestamp());
     write(1, "1 is thinking\n", 15);
   }
   else
   {
      fprintf (stderr, "%s", strerror (ret));
   }
   pthread_join (thread_philo, NULL);
   return EXIT_SUCCESS;
}
