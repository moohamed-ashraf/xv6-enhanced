#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int main(int argc, char *argv[])
{
  if(argc == 2 && strcmp(argv[1], "?") == 0) {
    printf("Usage: count keys intturupt \n");
    exit(0);
  }
  uint64 kbd_count=kbdint();
  printf("Keyboard intrupt count: %ld\n",kbd_count);

}
