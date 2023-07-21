#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <errno.h>

#define PLAIN 0
#define CHOC 1
#define SHUG 2

#define SEMKEY 456

union semun {
	int val;
	struct semid_ds*buf;
	unsigned short *array;
	struct seminfo *__buf;	
};
