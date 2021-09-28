#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int
main(int argc, char *argv[]){
	char *err = "argument error!\n";
	if(argc < 2 || strlen(argv[1]) > 10){
		write(1, err, strlen(err));
		exit(-1);
	}

	
	int t = atoi(argv[1]);
	sleep(t);
	exit(0);
}
