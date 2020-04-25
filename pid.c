/* Pour les constantes EXIT_SUCCESS et EXIT_FAILURE */
#include <stdlib.h>
/* Pour fprintf() */
#include <stdio.h>
/* Pour fork() */
#include <unistd.h>
/* Pour perror() et errno */
#include <errno.h>
/* Pour le type pid_t */
#include <sys/types.h>

/* La fonction create_process duplique le processus appelant et retourne
   le PID du processus fils ainsi créé */
pid_t create_process(void)
{
    /* On crée une nouvelle valeur de type pid_t */
    pid_t pid;

    /* On fork() tant que l'erreur est EAGAIN */
    do {
	pid = fork();
    } while ((pid == -1) && (errno == EAGAIN));

    /* On retourne le PID du processus ainsi créé */
    return pid;
}

/* La fonction child_process effectue les actions du processus fils */
void child_process(void)
{
    printf(" Nous sommes dans le fils !\n"
	   " Le PID du fils est %d.\n"
	   " Le PPID du fils est %d.\n", (int) getpid(), (int) getppid());
}

/* La fonction father_process effectue les actions du processus père */
void father_process(int child_pid)
{
    printf(" Nous sommes dans le père !\n"
	   " Le PID du fils est %d.\n"
	   " Le PID du père est %d.\n", (int) child_pid, (int) getpid());
}

int main(void)
{
    pid_t pid = create_process();

    switch (pid) {
    /* Si on a une erreur irrémédiable (ENOMEM dans notre cas) */
    case -1:
	perror("fork");
	return EXIT_FAILURE;
	break;
    /* Si on est dans le fils */
    case 0:
	child_process();
	break;
    /* Si on est dans le père */
    default:
	father_process(pid);
	break;
    }

    return EXIT_SUCCESS;
}

