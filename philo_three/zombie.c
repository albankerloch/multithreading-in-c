
#include "philo_one.h"

int main()
{

  int i;
  pid_t forkResult;
  int stat;
//  bin		var;
//  struct s_test t;
//  test te;
  sem_t *sem_die;
  char str_die[2];

//  var.str_die[0] = 'd';
//	var.str_die[1] = '\0';
	//sem_unlink(var.str_die);
	//var.sem_die = sem_open(var.str_die, O_CREAT | O_EXCL, 0664, 1);
  //sem_unlink(var.str_die);
  //sem_wait(var.sem_die);
  str_die[0] = 'd';
  str_die[1] = '\0';
  sem_unlink(str_die);
  sem_die = sem_open(str_die, O_CREAT | O_EXCL, 0664, 1);
  sem_wait(sem_die);

  i = 0;
  while (i < 5 && forkResult != 0 && forkResult != -1)
  {
    forkResult = fork();
    /*printf("[%d] [%d] i=%d fork=%d\n", getppid(), getpid(), i, forkResult);
    if (forkResult == 0)
      printf("i=%d\n", i);*/
    i++;
  }

   //sem_wait(var.sem_die);

 //while ( (forkResult = waitpid(-1, &stat, WNOHANG)) > 0) 
 /*while ( (forkResult = waitpid(-1, &stat, 0)) > 0)
  {
    printf("child %d terminated\n", forkResult);
  }*/
  if (forkResult == 0)
  {
    printf("Child is running, processing.\n");
    printf("[%d] [%d] hi i=%d fork=%d\n", getppid(), getpid(), i, forkResult);
    sleep(5);
    printf("Child is done, exiting.\n");
    sem_post(sem_die);
    /* Parent... */
  }
  else if (forkResult != -1)
  {
    printf("Parent is waiting...\n");
    sem_wait(sem_die);
    //wait(NULL);
    printf("Parent is exiting...\n");
  }
  else
  {
    perror("Error while calling the fork function");
  }
  return 0;
}