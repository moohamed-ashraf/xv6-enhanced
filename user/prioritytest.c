#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int main() {
  int pid1 = fork();
  if(pid1 == 0) {
    setpriority(getpid(), 5);
    while(1) printf("Child A (priority 5)\n");
  }

  int pid2 = fork();
  if(pid2 == 0) {
    setpriority(getpid(), 3);
    while(1) printf("Child B (priority 3)\n");
  }

  int pid3 = fork();
  if(pid3 == 0) {
    setpriority(getpid(), 1);
    while(1) printf("Child C (priority 1)\n");
  }

  wait(0);
  wait(0);
  wait(0);

  return 0;
}
