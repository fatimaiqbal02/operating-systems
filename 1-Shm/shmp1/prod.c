#include "myheader.h"

int main(int argc, char *argv[]){
	char *cptr;
	int id;
	int *outptr, *inptr;
	student *students;
	
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
	*inptr = 0;
	*outptr = 0;
	students = (student *)(cptr + 8);
	
	while(1){
	
		while(((*inptr + 1) % BUFSIZE) == (*outptr)){
			printf("No space to write, so going to sleep.\n");
			sleep(1);
		}
		
		printf("Enter SID :");
		scanf("%d", &students[*inptr].SID);
		printf("Enter Name :");
		scanf("%s", students[*inptr].name);
		
		*inptr = (*inptr + 1) % BUFSIZE;
	}
	
	return 0;
}
