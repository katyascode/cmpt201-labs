#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

int main() {
  char path[256];
  pid_t pid;

  while (true) {
    printf("Enter a path:\n");
    fflush(stdout);

    scanf("%s", path);
    pid = fork();

    if (pid == 0) { // fork() returns 0 to the child: replace process
      execl(path, path, NULL);
      perror(
          "execl() failed"); // This will only print if execl returns an error.
    } else if (pid > 0) {
      // fork() returns the pid to the parent process: wait on the child process
      waitpid(pid, NULL, 0);
    } else if (pid == -1) {
      perror("fork() failed");
    }
  }
  return 0;
}
