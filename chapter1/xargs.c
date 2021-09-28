#include "user/user.h"
#include "kernel/param.h"

void
execCom(const char *command, const char *param){
  
}

void
xargs(const char *command, char *argv[]){
  char *p = argv[1];
  char line[MAXARG] = 0;
  int count = 0;
  while(*p != '\0'){
    if(*p == '\n'){
      
    }
    else{
      line[count++] = *p++;
    }
  }
}

int
main(int argc, char *argv[]){
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
	}
  xargs(argv[1], p);
	exit(0);
}
