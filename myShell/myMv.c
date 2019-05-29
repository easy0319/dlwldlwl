#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>

#include <dirent.h>

#define SIZE 100

int main(int argc, char* argv[]){
	DIR *dp;
	int fd1,fd2;
	int r_size,w_size;
	char buffer[SIZE];
	char path[SIZE];	
	struct stat statbuf;
	struct dirent *dent;

	if(argc != 3){
		perror(argv[1]);
		exit(1);
	}
	
	stat(argv[1], &statbuf);

	getcwd(path, SIZE);
	
	chdir(argv[2]);

	fd1 = open(argv[1], O_RDONLY);
	fd2 = open(argv[2], O_RDWR|O_CREAT|O_EXCL, 0664);
   
	r_size = read(fd1, buffer, SIZE);
	w_size = write(fd2, buffer, r_size);

	while(r_size == SIZE){
		r_size = read(fd1, buffer, SIZE);
        	w_size = write(fd2, buffer, r_size);
    	}

	rename(argv[2], argv[1]);

	chdir(path);

	if(!S_ISDIR(statbuf.st_mode)){
    		unlink(argv[1]);
	}
	else{
		if(rmdir(argv[1]) == -1){
			perror(argv[1]);
			exit(1);
		}
	}
	
    	return 0;
}
