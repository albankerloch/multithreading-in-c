// C program to demonstrate working of Semaphores 
// compile with gcc open_sem.c -lpthread -lrt
#include <stdio.h> 
#include <pthread.h> 
#include <semaphore.h> 
#include <unistd.h> 
#include <sys/stat.h>
#include <fcntl.h> 

sem_t mutex;
sem_t *t; 


void* thread(void* arg) 
{ 
    //wait 
    sem_wait(t);

    printf("\nEntered..\n"); 
  
    //critical section 
    sleep(4); 
      
    //signal 
    printf("\nJust Exiting...\n"); 
    sem_post(t);

} 
  
  
int main() 
{ 
    //sem_init(&mutex, 0, 2); 
    //sem_init(&mutex, 0, 1);
    //t = &mutex;
    //t = sem_open("die", O_CREAT, 0664, 1);
  t = sem_open("/die", O_CREAT, S_IRWXU, 3);
  
    pthread_t t1,t2; 
    pthread_create(&t1,NULL,thread,NULL); 
    sleep(2); 
    pthread_create(&t2,NULL,thread,NULL); 
    pthread_join(t1,NULL); 
    pthread_join(t2,NULL); 
    sem_destroy(&mutex); 
    return 0; 
} 
