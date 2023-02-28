#include <signal.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/errno.h>
#include <stdio.h>

/*int
     execve(const char *path, char *const argv[],
         char *const envp[]);*/

int main()
{
  int   st;
  char  *argv[] = {"sleep", "10", NULL};

  if (fork() == 0)
    execve("/bin/sleep", argv, NULL);
  else
  {
    signal(SIGINT, SIG_IGN);
    wait(&st);
    printf("%d\n", wait);
    printf("%d\n", errno);
  }

}
