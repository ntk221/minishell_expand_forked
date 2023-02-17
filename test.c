#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <fcntl.h>
 
int main(int argc, char** argv)
{
    pid_t pid;
    int status;
    int fd;
    int pipe_[2];
 
    pipe(pipe_);
    pid = fork();
    if ( pid < 0 ) {
        perror("fork()");
        return -1;
    }
    if (pid == 0) {
        fd = open("new.txt", O_CREAT | O_WRONLY, 0666);
        dup2(fd, 1);
        execl("/bin/ls", "ls", (char *)NULL);
 
    } else {
        waitpid(pid, &status, 0);
        printf ("child process (PID = %d) finished\n", pid);
    }
 
    return 0;
}