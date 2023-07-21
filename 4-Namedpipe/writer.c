#include<unistd.h>
#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include<fcntl.h>
#include<limits.h>
#include<sys/types.h>
#include<sys/stat.h>

#define BUFFER_SIZE PIPE_BUF

int main(int argc, char *argv[]){
	int res, pipe_fd;
	char buffer[BUFFER_SIZE + 1];
	
	printf("Process %d going to open %s for writing\n", getpid(), argv[1]);
	
	if((pipe_fd = open(argv[1], O_WRONLY)) == -1){
		perror("Unable to open pipe");
		return 1;
	}
	
	sprintf(buffer, "Process %d says AOA", getpid());
	if((res = write(pipe_fd, buffer, BUFFER_SIZE)) == -1){
		perror("Unable to write the pipe");
		return 1;
	}

	close(pipe_fd);
}
