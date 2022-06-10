#include <stdio.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <strings.h>
#include <unistd.h>
#include <time.h>
#include <stdbool.h>

#include "../errorCode.h"
#include "../sharedFunctions.h"

#define MAX_BUFFER_LENGTH 50
//TODO refactor

int main() {

    srand(time(0));

    int sockFd, serverSocketLength;
    long sendReceiveSuccess;
    unsigned int fromAddressLength = sizeof(struct sockaddr_in);;
    struct sockaddr_in serverSocket;
    struct sockaddr_in from;

    char bufferReceive[MAX_BUFFER_LENGTH];
    char bufferSend[MAX_BUFFER_LENGTH];

    unsigned long long timeStampStart = 0;
    unsigned long long timeStampEnd = 0;


    if((sockFd = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
        printError(SOCKET_ERROR);
        exit(EXIT_FAILURE);
    }

    serverSocketLength = sizeof(serverSocket);
    bzero(&serverSocket, serverSocketLength);

    serverSocket.sin_family=AF_INET;
    serverSocket.sin_addr.s_addr=INADDR_ANY;
    serverSocket.sin_port=htons(SERVER_PORT);

    if (bind(sockFd, (struct sockaddr *)&serverSocket, serverSocketLength) < 0)
    {
        printError(BIND_ERROR);
        exit(EXIT_FAILURE);
    }

    while(true) {

        sendReceiveSuccess = recvfrom(sockFd, bufferReceive, MAX_BUFFER_LENGTH, 0, (struct sockaddr *)&from, &fromAddressLength);
        if (sendReceiveSuccess > 0) {
            printf("Received a datagram\n");
            timeStampStart = current_timestamp();

            //TODO implement sensor, delete mockup, if servers mic is malfunction serverSocket should send 0 or nothing at all
            int num = (rand() % (10 - 1 + 1)) + 1;
            //int num = (rand() % (10 - 9 + 1)) + 1;
            sleep(num);
            //End mockup

            timeStampEnd = current_timestamp();
            snprintf(bufferSend, MAX_BUFFER_LENGTH, "%llu\n", timeStampEnd - timeStampStart);

            sendReceiveSuccess = sendto(sockFd, bufferSend, MAX_BUFFER_LENGTH, 0, (struct sockaddr *) &from, fromAddressLength);
            if (sendReceiveSuccess < 0) {
                printError(SEND_ERROR);
            } else {
                printf("Send success\n");
            }
        } else {
            printError(RECEIVE_ERROR);
        }
    }
}