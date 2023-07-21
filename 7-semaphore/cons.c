#include "myheader.h"

int main(void)
{
	int sem_id;
	struct sembuf sops[3];
	union semun arg;
	unsigned short dcount[3];
	
	sem_id = semget(SEMKEY, 3, 0666);

	if(sem_id < 0)
		perror("Cannot get semaphore\n");
	else {
		arg.array = dcount;
		
		if(semctl(sem_id, 0, GETALL, arg) == -1) {
			perror("semctl");
			exit(1);
		}
		
		printf("\nPlain: %hu, Chocolate: %hu, Sugar: %hu\n", arg.array[PLAIN], arg.array[CHOC], arg.array[SHUG]);

		printf("\nEnter how many plain, chocolate and sugar donuts you want to Consume:");
		scanf("%hu %hu %hu", &arg.array[PLAIN], &arg.array[CHOC], &arg.array[SHUG]);
		
		sops[PLAIN].sem_num = PLAIN;
		sops[PLAIN].sem_op = 0-arg.array[PLAIN];
		sops[PLAIN].sem_flg = 0;
		
		sops[CHOC].sem_num = CHOC;
		sops[CHOC].sem_op = 0-arg.array[CHOC];
		sops[CHOC].sem_flg = 0;
		
		sops[SHUG].sem_num = SHUG;
		sops[SHUG].sem_op = 0-arg.array[SHUG];
		sops[SHUG].sem_flg = 0;
		
		if(semop(sem_id, sops,3) < 0)
			perror("Semop error");
		else
			semctl(sem_id, 0, GETALL, arg);
		
		printf("\nNew values are PLAIN: %d, Chocolate: %d, Sugar: %d \n", arg.array[PLAIN], arg.array[CHOC], arg.array[SHUG]);
	}
		
	return 0;
}
