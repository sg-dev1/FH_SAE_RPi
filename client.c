// Client side implementation of UDP client-server model
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>

#include <sys/time.h>
#include "common.h"


// Driver code
int main() {
	int sockfd;
	char buffer[BUFF_SIZE];
    char msg[BUFF_SIZE] = {0x15, };
	
	struct sockaddr_in	 servaddr;

	// Creating socket file descriptor
	if ( (sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0 ) {
		perror("socket creation failed");
		exit(EXIT_FAILURE);
	}

	memset(&servaddr, 0, sizeof(servaddr));
	
	// Filling server information
	servaddr.sin_family = AF_INET;
	servaddr.sin_port = htons(PORT);
	servaddr.sin_addr.s_addr = inet_addr("192.168.0.122");

    // Say hello to the server
    for (size_t i = 0; i < sizeof(msg); ++i) printf("%02x", msg[i]);

    sendto(sockfd, (const char *)msg, BUFF_SIZE, MSG_CONFIRM, (const struct sockaddr *) &servaddr, sizeof(servaddr));

	return 0;
}