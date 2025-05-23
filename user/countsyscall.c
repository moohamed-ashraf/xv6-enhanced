#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int main(int argc, char *argv[])
{
  if(argc == 2 && strcmp(argv[1], "?") == 0) {
    printf("Usage: count syscalls \n");
    exit(0);
  }
  uint64 coun=countsyscall();
  printf("syscall count: %ld\n",coun);

}
