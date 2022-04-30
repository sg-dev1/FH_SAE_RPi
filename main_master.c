#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>

#include "settings.h"


int main() {
    int sockfd;
    char buffer[BUFF_SIZE];
    char msg[BUFF_SIZE] = {'s'};
    struct sockaddr_in servaddr, cliaddr;
    char client_list[3][2] = { {0x15, 0x00}, {0x25, 0x00}, {0x35, 0x00} };
    
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
    while(client_list[0][1] == 0x00 || client_list[1][1] == 0x00 || client_list[2][1] == 0x00)
    {
        n = recvfrom(sockfd, (char *)buffer, BUFF_SIZE, MSG_WAITALL, ( struct sockaddr *) &cliaddr, &len);

        printf("Server received: ");
        for (int i = 0; i < BUFF_SIZE; i++) {
            printf("%x ", buffer[i]);
        }
        printf("\n");

        for (int i = 0; i < 3; i++) {
            if(buffer[0] == client_list[i][0]) {
                client_list[i][1] = 0x01;
                printf("Client %x connected\n", client_list[i][1]);
            }
        }
    }

    printf("All 3 clients are connected\n");
    
    // Broadcast timestamp
    // Wait X seconds
    // Broadcast "start measurement"
    // Play audio
    // Wait X seconds
    // If received -> Calc results; if not -> Display error
    
    return 0;
}
