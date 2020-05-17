#include "philo_one.h"

int main() {
  pid_t forkStatus;
  char str_die[2];
  sem_t *sem_die;
  int i;

  str_die[0] = 'd';
  str_die[1] = '\0';
  sem_unlink(str_die);
  sem_die = sem_open(str_die, O_CREAT | O_EXCL, 0664, 1);
  sem_wait(sem_die);

  i = 0;
  while (i < 5 && forkStatus != 0 && forkStatus != -1)
  {
    forkStatus = fork();
    if (forkStatus == 0)
      printf("Child is created.\n");
    i++;
  }

  /* Child... */
  if        (forkStatus == 0)
  {
    printf("Child is running, processing.\n");
    sleep(5);
    printf("Child is done, exiting.\n");
    sem_post(sem_die);
    /* Parent... */
  }
  else if (forkStatus != -1)
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
