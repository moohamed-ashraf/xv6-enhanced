#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int main(int argc, char *argv[])
{
  if(argc == 2 && strcmp(argv[1], "?") == 0) {
    printf("Usage: get ppid \n");
    exit(0);
  }
  uint64 ppid=getppid();
  printf("ppid: %ld\n",ppid);

}
