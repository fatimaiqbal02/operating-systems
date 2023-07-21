#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>

void error(const char *msg) {
 perror(msg);
 exit(1);
}

int main(int argc, char *argv[]) {
 	int sockfd, newsockfd, portno, clientCount = 0;
 	socklen_t clilen;
 	char c;
 	pid_t childpid;

 	struct sockaddr_in serv_addr, cli_addr;
 	int n;
	
 	if(argc < 2) {
  		fprintf(stderr, "Error, no port number provided.");
  		exit(1);
 	}
	
 	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	
 	if(sockfd < 0) {
  		error("Error while opening port");
 	}
	
 	bzero((char *) &serv_addr, sizeof(serv_addr));
 	portno = atoi(argv[1]);
 	serv_addr.sin_family = AF_INET;
 	serv_addr.sin_addr.s_addr = INADDR_ANY;
	serv_addr.sin_port = portno;
	
 	if(bind(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0) {
  		error("Error while binding.");
 	}
	
 	listen(sockfd, 5);
 	clilen = sizeof(cli_addr);
	
 	while(1) {
  		newsockfd = accept(sockfd, (struct sockaddr *) &cli_addr, &clilen);
  
  		if(newsockfd < 0) {
   			error("Error while accepting.");
  		}
  
  		if((childpid = fork()) < 0) {
   		error("Error while forking.");
		}
  
 		clientCount++;
  
 		if(childpid == 0) {
   			close(sockfd);
   
   			do{
   				if((n = read(newsockfd, &c, 1)) < 0) {
     					error("Error while reading from socket.");
    				}	
    
   		 		printf("Received (from client %d): %c \n",clientCount, c);
   		 		c++;
    		
   	 			if((n = write(newsockfd, &c, 1)) < 0) {
   	  				error("Error while writing to socket.");
   	 			}
   
   			} while(--c != 'Q');
 	         }
  
 	 	close(newsockfd);
 	}
}
