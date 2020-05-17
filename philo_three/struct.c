#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h> 
#include <sys/file.h>
#include <sys/mman.h>
#include <sys/wait.h>

typedef struct Data {
    char * name;
} Data;

void error_and_die(const char *msg) {
    perror(msg);
    exit(EXIT_FAILURE);
}

int main(int argc, char *argv[])
{
    int r;

    const char *memname = "sample";
    const size_t region_size = sysconf(_SC_PAGE_SIZE);

    int fd = shm_open(memname, O_CREAT | O_TRUNC | O_RDWR, 0666);
    if (fd == -1)
        error_and_die("shm_open");

    r = ftruncate(fd, region_size);
    if (r != 0)
        error_and_die("ftruncate");

    void *ptr = mmap(0, region_size, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);

    if (ptr == MAP_FAILED)
        error_and_die("mmap");
    close(fd);

    Data * data = ptr;

    pid_t pid = fork();

    if (pid == 0) {
        strcpy(data->name, "bob");
        printf("CHILD child wrote %s\n", (*(Data *)ptr).name);
        exit(0);
    }
    else {
        int status;
        waitpid(pid, &status, 0);
        printf("PARENT child wrote %s\n", (*(Data *)ptr).name);
    }   
    return 0;
}