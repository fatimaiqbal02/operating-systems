/* 	
 	Name: Fatima Iqbal Mirza
	Description: Implemenation of Dining Philospher problem using SystemV semaphore and pthread library in C.
*/

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <errno.h>
#include <pthread.h>
#include <time.h>

#define N 5
#define SEMKEY 458
#define LEFT i
#define RIGHT (i+1) % N

union semun {
	int val;
	struct semid_ds*buf;
	unsigned short *array;
	struct seminfo *__buf;	
};

int sem_id;
int philospohers[N] = {1, 2, 3, 4, 5};


void eat(int i){	
    struct sembuf sops[2];
    sops[0].sem_num = LEFT;
    sops[0].sem_op = -1;
    sops[0].sem_flg = 0;
    sops[1].sem_num = RIGHT;
    sops[1].sem_op = -1;
    sops[1].sem_flg = 0;
    semop(sem_id, sops, 2);
	
    printf("Philosopher # %d going to eat\n\n", i);
}

void think(int i){
    struct sembuf sops[2];
    sops[0].sem_num = LEFT;
    sops[0].sem_op = 1;
    sops[0].sem_flg = 0;
    sops[1].sem_num = RIGHT;
    sops[1].sem_op = 1;
    sops[1].sem_flg = 0;
    semop(sem_id, sops, 2);
	
    printf("Philosopher # %d done eating, Now going to think\n\n", i);
	
}
void randomDelayTime(){
	int delay = rand() % 6 +1;
	sleep(delay);
}

void* DiningPhilosopher(void* arg) {
    int* id = (int*)arg;
    while (1) {
    	randomDelayTime();		
   	printf("Philosopher # %d wants to eat\n\n",*id);
        randomDelayTime();
        eat(*id);
        randomDelayTime();
        think(*id);
        randomDelayTime();
    }
}

int main(void)
{
	union semun arg;
	unsigned short chopsticks[5];
	pthread_t pid[N];
	int i;
	
	sem_id = semget(SEMKEY, 5, (IPC_CREAT|IPC_EXCL|0666));
	
	if(sem_id < 0) {
		perror("Cannot create semaphore\n");
	} else {
		for(int i = 0; i<5;i++){
		    chopsticks[i] = 1;
		}
		arg.array = chopsticks;
		
		if (semctl(sem_id, 0, SETALL, arg) == -1) {
		    perror("semctl");
		    exit(1);
		}
	}
	
	for(int i = 0; i<5; i++){
		pthread_create(&pid[i], NULL, DiningPhilosopher, &philospohers[i]);
	}
		
	for(int i = 0; i<5; i++){
		pthread_join(pid[i], NULL);
	}
		
	return 0;		
}

/*
Sample Output:
philosopher # 0 wants to eat
philosopher # 2 wants to eat
philosopher # 2 going to eat
philosopher # 1 wants to eat
philosopher # 3 wants to eat
philosopher # 4 wants to eat
philosopher # 2 done eating, now going to think
philosopher # 1 going to eat
philosopher # 1 done eating, now going to think
philosopher # 2 wants to eat
philosopher # 2 going to eat
philosopher # 2 done eating, now going to think
philosopher # 1 wants to eat
philosopher # 1 going to eat
*/