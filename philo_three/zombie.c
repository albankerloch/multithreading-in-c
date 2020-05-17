
#include "philo_one.h"

void main()
{

  int i;
  pid_t forkResult;
  int stat;
  int a;
//  bin		var;
  struct s_test t;
  test te;
  sem_t *sem_die;
 // char str[2];

//  var.str_die[0] = 'd';
//	var.str_die[1] = '\0';
	//sem_unlink(var.str_die);
	//var.sem_die = sem_open(var.str_die, O_CREAT | O_EXCL, 0664, 1);
  //sem_unlink(var.str_die);
  //sem_wait(var.sem_die);
  //str_die[0] = 'd';
  //str_die[1] = '\0';
// sem_die = sem_open("die", O_CREAT | O_EXCL, 0664, 1);

  i = 0;
  while (i < 5 && forkResult != 0 && forkResult != -1)
  {
    forkResult = fork();
    printf("[%d] [%d] i=%d fork=%d\n", getppid(), getpid(), i, forkResult);
    if (forkResult == 0)
      printf("i=%d\n", i);
    i++;
  }

  printf("[%d] [%d] hi i=%d fork=%d\n", getppid(), getpid(), i, forkResult);

  //sem_wait(var.sem_die);

 //while ( (forkResult = waitpid(-1, &stat, WNOHANG)) > 0) 
 while ( (forkResult = waitpid(-1, &stat, 0)) > 0)
  {
    printf("child %d terminated\n", forkResult);
  }
}