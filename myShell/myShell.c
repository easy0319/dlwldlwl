#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <dirent.h>
//#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <wait.h>

#define MAX_SIZE 1024
#define SEPS " \t\n"

char* my_getcwd(char *user_name);
void execute(char *cmd);

int parser(char *cmd, char** args);

void mycd(char *cmd);
void myecho(char *cmd, int count);
void myhistory(char *hist[], int current);
void mypwd();
void mymkdir(char *dir[], int count);
void myrmdir(char *dir[], int count);

int main(int argh, char** argue, char**env){
	char line[MAX_SIZE];
	char *cwd;
	char user_name[MAX_SIZE];
	char host_name[MAX_SIZE];
	getlogin_r(user_name, MAX_SIZE);
	gethostname(host_name, MAX_SIZE);

	//history
	char *hist[100];
	int i, current = 0;
	for(i = 0; i < 100; i++){
		hist[i] = NULL;
	}

	while(1){
		cwd = my_getcwd(user_name);
		fprintf(stdout, "%s@%s:%s$ ", user_name, host_name, cwd);
		if(!fgets(line, sizeof(line) - 1, stdin)) break;
		if(strcmp(line, "\n") == 0) continue;	
	
		free(hist[current]);
		hist[current++] = strdup(line);

		if(line[strlen(line) - 1] == '\n')
			line[strlen(line) - 1] = '\0';

		if(!strcmp(line, "history")){
			myhistory(hist, current);
			continue;
		}		

		execute(line);
	}
	return EXIT_SUCCESS;
}

char* my_getcwd(char *user_name){
	char* cwd;
	char* word[MAX_SIZE];
	char* home_path;
	int str_len;

	home_path = (char *)malloc(strlen(user_name) + strlen("/home/")) + 1;
	home_path[strlen(user_name) + strlen("/home/")] = '\0';
	sprintf(home_path, "/home/%s",user_name);
	cwd = getcwd(NULL, BUFSIZ);
	if(strstr(cwd, home_path) == NULL){
		return cwd;
	}
	else{
		str_len = strlen(home_path);
		cwd[str_len - 1] = '~';
		return &cwd[str_len - 1];
}
}

void execute(char *cmd){
	char *args[MAX_SIZE];
	char user_name[MAX_SIZE];
	char host_name[MAX_SIZE];
	char path[MAX_SIZE];

	args[1] = '\0';
	args[2] = '\0';
	
	pid_t pid;
	getlogin_r(user_name, MAX_SIZE);
	gethostname(host_name, MAX_SIZE);
	
	char *my_home_path;
	my_home_path = (char *)malloc(strlen(user_name) + strlen("/home/")) + 1;
	my_home_path[strlen(user_name) + strlen("/home/")] = '\0';
	sprintf(my_home_path, "/home/%s",user_name);

	strcpy(path, my_home_path);
	strcat(path, "/ms/");

	//echo
	char *echo = (char*)malloc(strlen(cmd)) + 1;
	strcpy(echo, cmd);

	//parser
	int count = parser(cmd, args);

	//fork
	pid = fork();
	
	if(pid == -1){
		perror("fork fail\n");
		exit(1);
	}
	else if(pid == 0){	
		//child process..
		if(!strcmp(args[0], "mv")){
			strcat(path,"myMv");
			if(execvp(path, args) == -1){
				perror("execvp");
				exit(2);
			}			
		}
		else if(!strcmp(args[0], "cp")){
			strcat(path,"myCp");
			if(execvp(path, args) == -1){
				perror("execvp");
				exit(2);
			}
		}
		else if(!strcmp(args[0], "date")){
			strcat(path,"myDate");
			if(execvp(path, args) == -1){
				perror("execvp");
				exit(2);
			}
		}
                else if(!strcmp(args[0], "exit") ||
				!strcmp(args[0], "cd") ||
				!strcmp(args[0], "echo") ||
				!strcmp(args[0], "pwd") ||
				!strcmp(args[0], "mkdir") ||
				!strcmp(args[0], "rmdir"))
			exit(2);
		else if(execvp(args[0], args) == -1){	
			perror("execvp");
			exit(2);
                }
	}
	else{
		//printf("parent process...\n");
		wait(NULL);
	}

	if(!strcmp(args[0], "exit")){
		exit(0);
	}
	
	else if(!strcmp(args[0], "cd")){
		if(args[1] == '\0' /*|| !strcmp(args[1],"")*/)
			mycd("/home/");
		else{
			mycd(args[1]);
		}	
	}

	else if(!strcmp(args[0], "echo")){
		if(args[1] != '\0')
			myecho(echo, strlen(echo));
	}

	else if(!strcmp(args[0], "pwd")){
		mypwd();
	}
	
	else if(!strcmp(args[0], "mkdir")){
		mymkdir(args, count);
	}
	
	else if(!strcmp(args[0], "rmdir")){
		myrmdir(args, count);
	}

}

int parser(char *cmd, char **args){
	int count = 0;	
	char *tok;

	tok = strtok(cmd, SEPS);
	while(tok){
		args[count++] = tok;
		tok = strtok(NULL, SEPS);
	}
	
	return count;
}

void mycd(char *cmd){
	char username[MAX_SIZE];
	getlogin_r(username, MAX_SIZE);
	char *buf = (char*)malloc(strlen(username)) + 1;

	
	if(!strcmp(cmd, "/home/")){
		strcpy(buf, cmd);
		strcat(buf, username);
		chdir(buf);
	}	
	else{
		chdir(cmd);
	}
}

void myecho(char *cmd, int count){
	int i;

	for(i = 5; i < count; i++){
		printf("%c", cmd[i]);
	}
	printf("\n");
}

void myhistory(char *hist[], int current){
	int i = 0, j = 1;

        do {
		printf(" %d  %s", j++, hist[i++]);
        } while (i != current);
}

void mypwd(){
	char cwd[MAX_SIZE];
	getcwd(cwd, sizeof(cwd));
	printf("%s\n", cwd);
}

void mymkdir(char *dir[], int count){
	int i;

	if(count < 2){
		perror(dir[0]);
		return;
	}
	
	for(i = 1; i < count; i++){
		if(mkdir(dir[i], 0755) == -1){
			perror(dir[i]);
		}
	}
}

void myrmdir(char *dir[], int count){
	int i;

	if(count < 2){
		perror(dir[0]);
		return;
	}

	for(i = 1; i < count; i++){		
		if(rmdir(dir[i]) == -1){
			perror(dir[i]);
		}
	}
}
