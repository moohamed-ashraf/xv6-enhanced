#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int main() {
  int pid = fork();

  if (pid < 0) {
    printf("Fork failed!\n");
    exit(1);
  }

  if (pid == 0) {
    // Child process
    int child_pid = getpid();
    int parent_pid = getppid();
    printf("Child: my pid = %d, my parent pid = %d\n", child_pid, parent_pid);
    exit(0);
  } else {
    // Parent process
    wait(0);
    int parent_pid = getpid();
    printf("Parent: my pid = %d\n", parent_pid);
  }

  exit(0);
}
