#include "kernel/types.h"
#include "user/user.h"
#include "kernel/fs.h"
#include "kernel/stat.h"

#define COM_ERR "argument error: "
#define RET_ERR "this function run error:"

void
print_err(int flag, const char *msg){
	if(1 == flag){
		printf("%s%s\n", COM_ERR, msg);
	}
	else{
		printf("%s%s\n", RET_ERR, msg);
	}
}

int
initFile(const char *path, int *fd, struct stat *st){
	if((*fd = open(path, 0)) < 0){
		print_err(1, "find: cannot open this dir");
		return -1;
	}

	if(fstat(*fd, st) < 0){
		print_err(1, "find: cannot stat this dir");
		return -1;
	}

	return 0;
}

int 
getFileType(const char *path){
	int fd;
	struct stat st;

	initFile(path, &fd, &st);
	int pathT = 0;
	switch(st.type){    //dir is 1 and file is 2
		case T_DIR:
			pathT = 1;
			break;
		case T_FILE:
			pathT = 2;
			break;
	}
	close(fd);
	return pathT;
}

void
find(const char *dir, const char *file){
	int fd;
	struct stat st;
	struct dirent de;
	char buf[512];
	char *p;
	
	strcpy(buf, dir);
	p = buf + strlen(dir);
	*p++ = '/';

	initFile(dir, &fd, &st);
	
	while(read(fd, &de, sizeof(de)) == sizeof(de)){
		if(0 == de.inum){
			continue;
		}
		if(0 == strcmp(de.name, ".") || 0 == strcmp(de.name, "..")){
			continue;
		}
		if(getFileType(de.name) == 1){
			strcpy(p, de.name);
			find(buf, file);
      //*p = '0';
      strcpy(p, "");
		}
		else{
      //printf("now dir is %s\n", buf);
			if(strcmp(de.name, file) == 0){
				printf("%s%s\n", buf, file);
			}
		}
	}
	
	
}

int
main(int argc, char *argv[]){
	if(argc != 3 && (getFileType(argv[1]) != 1) && (getFileType(argv[2]) != 2)){
		print_err(1, "find directionname filename");
		exit(-1);
	}
	find(argv[1], argv[2]);
	exit(0);
}
