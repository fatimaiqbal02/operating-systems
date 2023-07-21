#include <arpa/inet.h>
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
	
	int s1, s2;
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
		
		if((n = read(newsockfd, &s1, sizeof(short))) < 0) {
		error("Error while reading from socket.");
		}
	
		printf("Received %d from client in Big Indian\n",s1);
		
		s1 = ntohs(s1);
		printf("Converted into Little Endian = %d \n", s1);
		
		s1++;
		printf("Incremented value of s1: %d\n", s1);

	
		s1 = htons(s1);
		printf("The value of s1 is in big indian is %d\n", s1);
		printf("Sending (to client - Big Endian): %d \n", s1);
	
		if((n = write(newsockfd, &s1, sizeof(short))) < 0) {
			error("Error while writing to socket.");
		}
						
		close(newsockfd);
	}
}
