#include "kernel/types.h"
#include "user/user.h"

int
main(int argc, char *argv){
	int pChR[2];
	int pPaR[2];
	if(-1 == pipe(pChR) || -1 == pipe(pPaR)){
		char *pErr = "allocation of pipe happened error!\n";
		write(1, pErr, strlen(pErr));
		exit(-1);
	}

	int pid = fork();
	if(pid == 0){	//child process
		close(pPaR[0]);
		close(pChR[1]);

		char c;
		read(pChR[0], &c, 1);
		printf("<%d>:received ping, and byte is %c\n", getpid(), c);

		char c2 = 'K';
		write(pPaR[1], &c2, 1);
		close(pPaR[1]);
		close(pChR[0]);
		exit(0);
	}
	else{	//parent process
		close(pPaR[1]);
		close(pChR[0]);

		char c = 'T';
		write(pChR[1], &c, 1);

		read(pPaR[0], &c, 1);
		printf("<%d>:received pong, and byte is %c\n", getpid(), c);
		close(pPaR[0]);
		close(pChR[1]);
		wait((int *)0);
		exit(0);
	}
}
