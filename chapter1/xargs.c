#include "kernel/types.h"
//#include "kernel/riscv.h"
//#include "kernel/defs.h"
#include "kernel/param.h"
#include "user/user.h"

//void
//execCom(const char *command, const char *param){
//}

void
forkAndExec(char *command, char *argv[]){
  int pid = fork();
  if(0 == pid){
    exec(command, argv);
    exit(1);
  }
  else{
    wait((int *)0);
  }
}

void
xargs(int argc, char *argv[]){
  char line[MAXARG] = {0};
  char *tmp_argv[MAXARG] = {0};
  int count = 0;
  char c;
  int ret;

  for(int i = 0; i < argc; ++i){
    tmp_argv[i] = argv[i];
  }

  while(1){
    ret = read(0, &c, 1);
    //printf("%c\n", c);
    if(0 == ret || '\n' == c){
      line[count] = 0;
      char tmp_arr[MAXARG];
      strcpy(tmp_arr, line);
      //printf("tmp_arr = %s\n", tmp_arr);
      tmp_argv[argc] = tmp_arr;

      forkAndExec(*argv, tmp_argv);
      //printf("command = %s", *argv);
      //for(int i = 0; i < argc; ++i){
      //  printf(", %s", tmp_argv[i]);
      //}
      //printf("\n");

      //memset(line, 0, MAXARG);
      count = 0;

      if(0 == ret){
        break;
      }
    }
    else{
      line[count++] = c;
    }
    //printf("line = %s\n", line);
  }
}

int
main(int argc, char *argv[]){
  int num = argc - 1;
  char **p = argv + 1;
	if(argc < 3){
		printf("error: xargs command [optional ..]\n");
		exit(-1);
	}
	if(0 == strcmp(argv[1], "-n")){
		if(0 != strcmp(argv[2], "1")){
			printf("error: not support other arguments except 1\n");
			exit(-1);
		}
    p += 2;
    num -= 2;
	}
  xargs(num, p);
  //printf("param = %d\n", num);
	exit(0);
}
