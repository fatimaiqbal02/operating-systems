#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>

int main(){
int fd[2];
pid_t pid;
int outfd;

if((pipe(fd)) == -1){
	perror("Unable to pipe");
	return 0;   //pipe creation failed
}

if((pid = fork()) == -1){
	perror("Unable to fork");
	return 0;	//fork call failed
}


if(pid == 0){		//child process
	dup2(fd[1], STDOUT_FILENO);
	close(fd[0]);
	close(fd[1]);
	execl("/usr/bin/ls", "ls", NULL);
	perror("Unable to load program");
	
}
if(pid > 0){		//parent process
	if((outfd = open("temp.txt", O_WRONLY | O_CREAT | O_TRUNC, 0666)) == -1){
		perror("Unable to open file");
		return 0;
	}
	dup2(outfd, STDOUT_FILENO);
	close(outfd);
	dup2(fd[0], STDIN_FILENO);
	close(fd[0]);
	close(fd[1]);	
	execl("/usr/bin/grep", "grep", "p" , NULL);
	perror("Unable to load program");
}
}
