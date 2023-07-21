#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/shm.h>

#define BUFSIZE 5

#define PERM (S_IRUSR | S_IWUSR | IPC_CREAT)

typedef struct{
	int SID;
	char name[10];
} student;

