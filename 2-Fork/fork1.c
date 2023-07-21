#include<stdio.h>
#include<unistd.h>

int main(void){
	int x;
	pid_t child_pid;
	x = 0;
	printf("Value of x is %d and my pid is %ld\n",x,(long)getpid());
	child_pid = fork();
	if(child_pid){
		x=5;
		printf("I am parent and my id is %ld, my child is %ld and my x is %d\n", (long)getpid(), (long)child_pid, x);
		sleep(1);
		return 0;
	}
	x = 1;
	printf("I am child process %ld, my parent is %ld and my x is %d\n",(long)getpid(), (long)getppid(), x);
	return 0;

}

