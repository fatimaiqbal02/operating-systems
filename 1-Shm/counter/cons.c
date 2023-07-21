#include "myheader.h"

int main(int argc, char *argv[]){
	char *cptr;
	int id;
	int *outptr, *inptr;
	student *students;
	int *counter;
	
	if((id = shmget(123, 100, PERM)) == -1){
		perror("Failed to create shared memory segment");
		return 1;	
	}
	
	if((cptr = (char*)shmat(id,NULL,0)) == (void*)-1){
		perror("Failed to attach memory segment");
		return 1;
	}
	
	inptr = (int *)(cptr);
	outptr = (int *)(cptr + 4);
	counter = (int *)(cptr + 8);
	students = (student *)(cptr + 12);
	
	while(1){
		
		while((*counter) == 0){
			printf("Nothing to read so going to sleep.\n");
			sleep(1);
		}
		
		printf("SID= %d, Name = %s\n",students[*outptr].SID, students[*outptr].name);
		
		*outptr = (*outptr + 1) % BUFSIZE;
		(*counter)--;
	}	
	return 0;
}
