#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>
#include <stdlib.h>
#include <poll.h>
#include "../errorCode.h"
#include "clientFunctions.h"
#include "../sharedFunctions.h"

/**
 * brief: function used in the threads. connects to PI (servers) and waits for response
 * if no response comes it times out (TIMEOUT)
 * @param arg the arguments needed to connect to the PI and to store the result
 * @return NULL
 */
void* connectToPi(void* arg) {
    long sendReceiveStatus;
    int sockFd;
    thread_data_t *threadData = (thread_data_t *)arg;
    threadData->result = 0;
    const char* ipAddressPI;

    char* bufferSend = "Send me stuff"; //TODO command to send to the PIs (not really important what is send because the servers have only one job)
    char bufferReceive[MAX_BUFFER_SIZE];

    struct pollfd pollFd;
    struct sockaddr_in server;
    unsigned int serverAddressLength = sizeof(struct sockaddr_in);

    pollFd.events = POLLIN | POLLPRI;
    sockFd = socket(AF_INET, SOCK_DGRAM, 0);
    if(sockFd < 0) {
        printError(SOCKET_ERROR);
        exit(EXIT_FAILURE);
    }
    pollFd.fd = sockFd;

    server.sin_family =AF_INET;
    server.sin_port = htons(SERVER_PORT);

    if(threadData->addr == 1) {
        ipAddressPI = "192.168.8.210";
    }else if (threadData->addr == 2) {
        ipAddressPI = "192.168.8.220";
    }else if (threadData->addr == 3) {
        ipAddressPI = "192.168.8.230";
    } else {
        printError(INVALID_IP_ADDRESS);
        exit(EXIT_FAILURE);
    }

    printf("Trying to connect to Pi: %s\n", (char*) ipAddressPI);

    if(inet_pton(AF_INET, ipAddressPI, &server.sin_addr) <= 0) {
        printError(INET_ADDR_ERROR);
        exit(EXIT_FAILURE);
    }

    sendReceiveStatus = sendto(sockFd, bufferSend, strlen(bufferSend), 0, (const struct sockaddr *) &server, serverAddressLength);
    if (sendReceiveStatus < 0) {
        printError(SEND_ERROR);
        exit(EXIT_FAILURE);
    }

    //if something is to poll we receive it with  recvfrom otherwise we run into the timeout
    if (poll(&pollFd, 1, TIMEOUT) > 0) {
        //poll successful
        sendReceiveStatus = recvfrom(sockFd, bufferReceive, MAX_BUFFER_SIZE, 0, (struct sockaddr *) &server, &serverAddressLength);
        if (sendReceiveStatus < 0) {
            printError(RECEIVE_ERROR);
            exit(EXIT_FAILURE);
        } else {
            char *b;
            threadData->result = strtol(bufferReceive, &b, 10);
            printf("Message received threadData->result: %llu\n", threadData->result);
        }
    } else {
        printError(TIMEOUT_REACHED);
    }

    return NULL;
}