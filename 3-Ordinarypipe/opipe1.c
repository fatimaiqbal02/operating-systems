#include <stdio.h>
#include <unistd.h>

int main(){
int fd[2];
pid_t pid;

if((pipe(fd)) == -1){
	perror("Unable to pipe");
	return 0;   //pipe creation failed
}

if((pid = fork()) == -1){
	perror("Unable to fork");
	return 0;	//fork call failed
}


if(pid == 0){		//child process
	printf("I am a child and process ID:%ld  parent ID:%ld  child ID:%ld\n",
        (long)getpid(), (long)getppid(), (long)pid);
	dup2(fd[1], STDOUT_FILENO);
	close(fd[0]);
	close(fd[1]);
	execl("/usr/bin/ls", "ls", NULL);
	perror("Unable to load program");
}
if(pid > 0){		//parent process
	printf("I am a parent and process ID:%ld  parent ID:%ld  child ID:%ld\n",
        (long)getpid(), (long)getppid(), (long)pid);
	dup2(fd[0], STDIN_FILENO);
	close(fd[1]);
	close(fd[0]);
	execl("/usr/bin/grep", "grep", "p" , NULL);
	perror("Unable to load program");
}
}


//in my code, first parent process will execute. it will write printf to terminal and then redirects stdIn to read end of pipe  and create another child process grep there and waits for the child program to exeute and end. then child process starts and write printf to terminal then redirects its stdOut to wrote end then starts another child process ls whose output wull be storef in write end of pipe and child process ececution ends. Now the grep prpcess of parent process will read from write end of pipe from ls?? is this the scenario?

//output
//printf statement of parent
//printf statement of child
//ls cmd
//grep command

