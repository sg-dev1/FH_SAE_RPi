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

#include "settings.h"


// Driver code
int main() {
	int sockfd;
	unsigned long int timestampBuffer;
	//char buffer[BUFF_SIZE];
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
	servaddr.sin_addr.s_addr = inet_addr("10.0.0.2");

    // Say hello to the server
    for (size_t i = 0; i < sizeof(msg); ++i) printf("%02x", msg[i]);

    sendto(sockfd, (const char *)msg, BUFF_SIZE, MSG_CONFIRM, (const struct sockaddr *) &servaddr, sizeof(servaddr));


	socklen_t len = 0;
	int n = 0;
	while(1) {
		printf("receiving\n");
		//n = recvfrom(sockfd, (char *)buffer, BUFF_SIZE, MSG_WAITALL, (struct sockaddr *) &servaddr, &len);
        //printf("Client received: %s\n", buffer);
		n = recvfrom(sockfd, &timestampBuffer, sizeof(timestampBuffer), MSG_WAITALL, (struct sockaddr *) &servaddr, &len);
		printf("[Client]Timestamp received: %lu\n", timestampBuffer);

		sleep(1);
		//Send ACK KEINE MESSAGE DAFÜR GEFUNDEN
		sendto(sockfd, (const char *)msg, BUFF_SIZE, MSG_CONFIRM, (const struct sockaddr *) &servaddr, sizeof(servaddr));

		//Receive "Start Measurement"
		n = recvfrom(sockfd, &buffer, sizeof(buffer), MSG_WAITALL, (struct sockaddr *) &servaddr, &len);
		printf("[Client]Message received: %x\n", buffer);
	}

	return 0;
}