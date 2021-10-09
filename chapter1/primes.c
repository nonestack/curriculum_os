#include "kernel/types.h"
#include "user/user.h"

void
child_work(int p[2]){
  close(p[1]);

  int ret;
  if(0 == read(p[0], &ret, sizeof(ret))){
    return ;
  }

  printf("prime %d\n", ret);

  int pp[2];
  int pid = -1;
  while(1){
    int num;
    if(0 == read(p[0], &num, sizeof(num))){
      break;
    }

    if(0 != num % ret){
      if(-1 == pid){
        pipe(pp);
        pid = fork();
        if(0 == pid){
          child_work(pp);
        }
        else{
          close(pp[0]);
        }
      }
      write(pp[1], &num, sizeof(num));
    }
  }
  if(-1 == pid){
    wait((int *)0);
  }
  exit(0);
}

void
primes(){
  close(0);
  int p[2];
  pipe(p);
  int pid = fork();
  if(0 == pid){
    child_work(p);
  }
  else{
    close(p[0]);
    for(int i = 2; i < 36; ++i){
      write(p[1], &i, sizeof(i));
    }
    close(p[1]);
    wait((int *)0);
  }
}

int
main(int argc, char *argv[]){
  primes();
  exit(0);
}
