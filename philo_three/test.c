// C program to demonstrate working of Semaphores 
#include <stdio.h> 
#include <pthread.h> 
#include <semaphore.h> 
#include <unistd.h> 
#include <fcntl.h> 
#include <sys/stat.h> 

sem_t mutex;
sem_t *t;

void* thread(void* arg) 
{
  (void)arg;
        //wait 
        sem_wait(t); 
        printf("\nEntered..\n"); 

        //critical section 
        sleep(4); 
        
        //signal 
        printf("\nJust Exiting...\n"); 
        sem_post(t);
        return (NULL);
} 

int main() 
{ 
  //sem_init(&mutex, 0, 1);
  //t = &mutex;
    char *str;

     str = "essai";
    sem_unlink(str);
    t = sem_open(str, O_CREAT | O_EXCL, 0644, 2);
//t = sem_open("/die", O_CREAT, S_IRWXU, 3); 
    pthread_t t1,t2; 
    pthread_create(&t1,NULL,thread,NULL); 
    sleep(2); 
    pthread_create(&t2,NULL,thread,NULL); 
    pthread_join(t1,NULL); 
    pthread_join(t2,NULL); 
    //sem_destroy(&mutex); 
    return 0; 
} 