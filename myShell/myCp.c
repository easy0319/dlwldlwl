#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>

#include <string.h>
#include <dirent.h>

#define SIZE 100

void filecopy(char *fd1, char *fd2, char *path, char *dest);
void dircopy(char *fd1, char *fd2, char *path, char *dest);

int main(int argc, char* argv[]){	
	DIR *dp;
	char dest[SIZE];
	char path[SIZE];
	struct stat statbuf;
	struct dirent *dent;

	if(argc != 3){
		perror(argv[1]);
		exit(1);
	}

	stat(argv[1], &statbuf);
	
	if(!S_ISDIR(statbuf.st_mode)){  //디렉토리가 아니면 참
		getcwd(path, SIZE);
		getcwd(dest, SIZE);
		filecopy(argv[1], argv[2], path, dest);
	}
	else{
		getcwd(path, SIZE);
		mkdir(argv[2], 0755);
	
		chdir(argv[2]);
		getcwd(dest, SIZE);
		chdir(path);

		dircopy(argv[1], argv[2], path, dest);
	}

	return 0;
}

void filecopy(char *fd1, char *fd2, char *path, char *dest){
	FILE *f1, *f2;
	char buf[SIZE];
	int c;

	chdir(path);
	if((f1 = fopen(fd1, "r")) == NULL){
		perror("file open failed");
		exit(1);
	}

	chdir(dest);
	if((f2 = fopen(fd2, "w")) == NULL){
		perror("file open failed");
		exit(1);
	}	
	
	chdir(path);

	while((c = fread(buf, 1, SIZE, f1)) > 0){
		if(fwrite(buf, 1, c, f2) == 0){
			perror("fwrite failed");
			exit(1);
		}
	}

	if(ferror(f1)){
		perror("");
		exit(1);
	}
	
	fclose(f1);
	fclose(f2);
}
void dircopy(char *fd1, char *fd2, char *path, char *dest){
	DIR *dp;
	struct dirent *entry;
	struct stat statbuf;
	
	if((dp = opendir(fd1)) ==NULL){
		perror(fd1);
		exit(1);
	}

	chdir(fd1);
		
	while((entry = readdir(dp)) != NULL){
		lstat(entry->d_name, &statbuf);

		if(S_ISDIR(statbuf.st_mode)){
			if(!strcmp(".", entry->d_name) || !strcmp("..",entry->d_name))
				continue;
	
			getcwd(path, SIZE);
			chdir(dest);
			mkdir(entry->d_name, 0755);
			chdir(entry->d_name);
			getcwd(dest, SIZE);
			chdir(path);

			dircopy(entry->d_name, entry->d_name, path, dest);
		}	
		else{
			getcwd(path, SIZE);
		
			filecopy(entry->d_name, entry->d_name, path, dest);
		}
	}
	
	getcwd(path, SIZE);
	chdir(dest);
	
	chdir("..");
	getcwd(dest, SIZE);

	chdir(path);
	chdir("..");

	closedir(dp);
}
