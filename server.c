#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>

#include "common.h"


int main() {
	int sockfd;
	char buffer[BUFF_SIZE];
	char msg[BUFF_SIZE] = {'s'};
	struct sockaddr_in servaddr, cliaddr;
	
	// Creating socket file descriptor
	if ( (sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0 ) {
		perror("socket creation failed");
		exit(EXIT_FAILURE);
	}
	
	memset(&servaddr, 0, sizeof(servaddr));
	memset(&cliaddr, 0, sizeof(cliaddr));
	
	// Filling server information
	servaddr.sin_family = AF_INET; // IPv4
	servaddr.sin_addr.s_addr = INADDR_ANY;
	servaddr.sin_port = htons(PORT);
	
	// Bind the socket with the server address
	if ( bind(sockfd, (const struct sockaddr *)&servaddr,
			sizeof(servaddr)) < 0 )
	{
		perror("bind failed");
		exit(EXIT_FAILURE);
	}
	
	socklen_t len = sizeof(cliaddr); //len is value/resuslt
    int n = 0;

	// Wait for all 3 clients to connect
	int client_cnt = 0;
    while(client_cnt != 3)
    {
		n = recvfrom(sockfd, (char *)buffer, BUFF_SIZE, MSG_WAITALL, ( struct sockaddr *) &cliaddr, &len);

		printf("Server received: ");
		for (int i = 0; i < BUFF_SIZE; i++) {
			printf("%x ", buffer[i]);
		}
        printf("\n");

		if (buffer[0] == 21 || buffer[0] == 37 || buffer[0] == 53)
		{
			client_cnt ++;
		}
		printf("client count: %d\n", client_cnt);
    }
	
	return 0;
}