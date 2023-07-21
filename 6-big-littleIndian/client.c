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
	exit(0);
}

int main(int argc, char *argv[]){
	
	int s1;
	int sockfd, portno, n, term_con = 0;
	struct sockaddr_in serv_addr;
	struct hostent *server;
	
	if(argc < 3){
		fprintf(stderr, "usage %s hostname port\n", argv[0]);
		exit(0);
	}
	
	portno = atoi(argv[2]);
	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	
	if(sockfd < 0){
		error("Error Opening socket");
	}
	
	server = gethostbyname(argv[1]);
	
	if(server == NULL){
		fprintf(stderr, "no such host\n");
		exit(0);
	}
	
	bzero((char *) &serv_addr, sizeof(serv_addr));
	serv_addr.sin_family = AF_INET;
	
	bcopy((char *)server->h_addr, (char *)&serv_addr.sin_addr.s_addr, server->h_length);
	serv_addr.sin_port = portno;
	
	if(connect(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0){
		error("Error Connecting\n");
	}
	
	
	s1 = 200;
	printf("the value of s1 is %d\n",s1);
	s1 = htons(s1);
	printf("the value of s1 in big indian is %d\n",s1);
	n = write(sockfd, &s1, sizeof(short));
		
	if(n < 0){
		error("Error writing to socket");
	}
	
	n = read(sockfd, &s1, sizeof(short));
		
	if(n < 0){
		error("Error reading from socket\n");
	}
		
	printf("I got %d from server\n", s1);
	
	close(sockfd);
		
}
