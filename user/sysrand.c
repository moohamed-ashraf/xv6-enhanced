#include "kernel/types.h"
#include "user/user.h"

int main(){
  for (int i=0; i<5; i++){
    printf("random number %d: %d\n",i+1, sysrand());
  }
  exit(0);
}
