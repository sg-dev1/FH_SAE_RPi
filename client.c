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

#define NODE_ID  1

// Driver code
int main() {
	int sockfd;
//	unsigned long int timestampBuffer;
	//char buffer[BUFF_SIZE];
	char buffer[REC_BUFF_SIZE] = {};
        char msg[SEND_BUFF_SIZE] = {(NODE_ID << 4) | 1};
	
	struct sockaddr_in	 servaddr;
#if 0
        struct sockaddr_in       cliaddr;
#endif // 0

	// Creating socket file descriptor
	if ( (sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0 ) {
		perror("socket creation failed");
		exit(EXIT_FAILURE);
	}

	memset(&servaddr, 0, sizeof(servaddr));
	
	// Filling server information
	servaddr.sin_family = AF_INET;
	servaddr.sin_port = htons(PORT);
	servaddr.sin_addr.s_addr = inet_addr("127.0.0.1");

#if 0
        cliaddr.sin_family = AF_INET;
        cliaddr.sin_port = htons(4242);
        cliaddr.sin_addr.s_addr = inet_addr("127.0.0.1");
#endif

        // Say hello to the server
        for (size_t i = 0; i < sizeof(msg); ++i) printf("%02x", msg[i]);
        printf("\n");

        sendto(sockfd, (const char *)msg, SEND_BUFF_SIZE, MSG_CONFIRM, (const struct sockaddr *) &servaddr, sizeof(servaddr));


	socklen_t len = 0;
	int n = 0;
	while(1) {
                sleep(1);

		printf("receiving\n");
                memset(buffer, 0, sizeof(buffer));
		n = recvfrom(sockfd, (char *)buffer, REC_BUFF_SIZE, MSG_WAITALL, (struct sockaddr *) &servaddr, &len);
                printf("Client Received: 0x %02x %02x %02x %02x %02x, n=%d\n", buffer[0], buffer[1], buffer[2], buffer[3], buffer[4], n);
                //printf("Client received: %x\n", buffer); // -- prints the address of the buffer
		//n = recvfrom(sockfd, &timestampBuffer, sizeof(timestampBuffer), MSG_WAITALL, (struct sockaddr *) &servaddr, &len);
		//printf("[Client]Timestamp received: %lu\n", timestampBuffer);

		sleep(1);
		msg[0] = (NODE_ID << 4) | 2;
		sendto(sockfd, (const char *)msg, SEND_BUFF_SIZE, MSG_CONFIRM, (const struct sockaddr *) &servaddr, sizeof(servaddr));

		//Receive "Start Measurement"
		n = recvfrom(sockfd, &buffer, sizeof(buffer), MSG_WAITALL, (struct sockaddr *) &servaddr, &len);
		printf("Received: 0x %02x %02x %02x %02x %02x, n=%d\n", buffer[0], buffer[1], buffer[2], buffer[3], buffer[4], n);
                //printf("[Client]Message received: %x\n", buffer); // -- prints the address of the buffer
                if (buffer[0] == 2) {
                  printf("Starting with the measurement ...\n");
                  break;
                }
	}

	return 0;
}
