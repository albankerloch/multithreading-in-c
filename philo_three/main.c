#include "philo_one.h"

long long	current_timestamp(void)
{
	struct timeval	te;
	long long		m;

	gettimeofday(&te, NULL);
	m = te.tv_sec * 1000LL + te.tv_usec / 1000;
	return (m);
}

int			main(int ac, char **av)
{
	pid_t forkStatus;
	char str_die[2];
	char str_fork[2];
	char str[50];
	sem_t *sem_die;
	sem_t *sem_fork;
	int i;
	bin var;
	long long start;

	if (ft_arg(&var, ac, av))
		return (1);
	(void)str;

	str_fork[0] = 'f';
	str_fork[1] = '\0';
	sem_unlink(str_fork);
	sem_fork = sem_open(str_fork, O_CREAT | O_EXCL, 0664, var.nb);
	str_die[0] = 'd';
	str_die[1] = '\0';
	sem_unlink(str_die);
	sem_die = sem_open(str_die, O_CREAT | O_EXCL, 0664, 1);
	sem_wait(sem_die);

	i = 0;
	while (i < var.nb && forkStatus != 0 && forkStatus != -1)
	{
		forkStatus = fork();
		i++;
	}

	/* Child... */
	if (forkStatus == 0)
	{
		printf("[%d] [%d] hi i=%d fork=%d\n", getppid(), getpid(), i, forkStatus);
		start = current_timestamp();
		(void)sem_fork;
		var.count_eat = 0;
		ft_message(i, " is thinking\n", start, 12, str);
		while (1)
		{
			sem_wait(sem_fork);
			sem_wait(sem_fork);
			ft_activity(i, str, &start, &var, sem_fork);
		}
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
