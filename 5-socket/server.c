#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>

void error (const char *msg){

	perror(msg);
	exit(1);
}

int main(int argc, char *argv[]){
	
	char c;
	int sockfd, portno, newsockfd;
	socklen_t clilen;
	struct sockaddr_in serv_addr, cli_addr;
	int n;
	
	if(argc < 2){
		fprintf(stderr, "no port provided\n");
		exit(1);
	}
	
	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	
	if(sockfd < 0){
		error("Error Opening socket");
	}
	
	bzero((char *) &serv_addr, sizeof(serv_addr));
	portno = atoi(argv[1]);
	
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_addr.s_addr = INADDR_ANY;
	serv_addr.sin_port = portno;
	
	if(bind(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0){
		error("Error on binding\n");
	}
	
	listen(sockfd, 5);
	clilen = sizeof(cli_addr);
		
	while(1){
	
		newsockfd = accept(sockfd, (struct sockaddr *) &cli_addr, &clilen);
		
		if(newsockfd < 0){
			error("Error on accepting\n");
		}
		
		do{
			n = read(newsockfd, &c, 1);
			
			if(n < 0){
				error("Error reading from socket");
			}
			
			printf("I got : %c\n", c);
			++c;
			
			n = write(newsockfd, &c, 1);
			
			if(n < 0){
				error("Error writing from socket");
			}
			
			
		} while(--c != '0');
		close(newsockfd);
	}
}
