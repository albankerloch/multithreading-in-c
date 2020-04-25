#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h> 
#include <unistd.h>
 
#define INITIAL_STOCK   20
#define NB_CLIENTS      5
 
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
 
int main (void)
{
   int ret;
   void *t;
   pthread_t thread_philo;
   
   ret = 0;
   printf ("Creation du thread du philosophe !\n");
   ret = pthread_create(&thread_philo, NULL, fn_philo, NULL);
 
   if (!ret)
   {
      printf ("Creation des threads clients !\n");
   }
   else
   {
      fprintf (stderr, "%s", strerror (ret));
   }
   pthread_join (thread_philo, NULL);
   return EXIT_SUCCESS;
}
