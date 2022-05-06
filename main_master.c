#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/time.h>
//#include <wiringPi.h>

#include "settings.h"

#define CPP_CLIENT

#define SPEAKER_PIN 7

struct Client {
    char ID;
    char connected;
    char ack;
    long round_time;
    int  time_diff;
};

void playAudio() {
#if 0
	for(int i = 0; i < 5; i++) {
        digitalWrite(SPEAKER_PIN, 1);
        delay(5);
        digitalWrite(SPEAKER_PIN, 0);
	    delay(5);
	}
#endif
}


int main() {

    struct Client c1 = {0x01, 0x00, 0x00, 0x00, 0x00};
    struct Client c2 = {0x02, 0x00, 0x00, 0x00, 0x00};
    struct Client c3 = {0x03, 0x00, 0x00, 0x00, 0x00};

#if 0
    // Init GPIO
    if(wiringPiSetup() == -1) {
        return 1;
    }
    pinMode(SPEAKER_PIN, OUTPUT);
#endif

    int sockfd;
    char buffer[REC_BUFF_SIZE];
    char msg[SEND_BUFF_SIZE] = {0x00};
    struct sockaddr_in servaddr, cliaddr, cliaddr2;
    
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

#ifdef CPP_CLIENT
    cliaddr2.sin_family = AF_INET;
    cliaddr2.sin_addr.s_addr = 0x010007f; // localhost
    cliaddr2.sin_port = htons(4242);
#endif // CPP_CLIENT

    // Bind the socket with the server address
    if ( bind(sockfd, (const struct sockaddr *)&servaddr, sizeof(servaddr)) < 0 ) {
        perror("bind failed");
        exit(EXIT_FAILURE);
    }
    
    socklen_t len = sizeof(cliaddr);
    int n = 0;

    #if !DEBUG

        // Wait for all 3 clients to connect & say hello
        while(c1.connected == 0x00)// || client_list[1][1] == 0x00 || client_list[2][1] == 0x00) // TODO: uncomment
        {
            n = recvfrom(sockfd, (char *)buffer, REC_BUFF_SIZE, MSG_WAITALL, ( struct sockaddr *) &cliaddr, &len);

            printf("Server received: ");
            for (int i = 0; i < REC_BUFF_SIZE; i++) {
                printf("%x ", buffer[i]);
            }
            printf("\n");

            if (buffer[0] == (c1.ID << 4 | 0x01)) {
                printf("C1 connected!\n");
                c1.connected = 0x01;
            }
            else if (buffer[0] == (c2.ID << 4 | 0x01)) {
                printf("C2 connected!\n");
                c2.connected = 0x01;
            }
            else if (buffer[0] == (c3.ID << 4 | 0x01)) {
                printf("C3 connected!\n");
                c3.connected = 0x01;
            }
        }

        printf("All 3 clients are connected\n");
        //struct sockaddr *cliaddr_ptr = ( struct sockaddr *)&cliaddr;
        //printf("Client address: %s\n", cliaddr_ptr->sa_data);
        printf("Client port: %d\n", cliaddr.sin_port);
        printf("Address: %08x\n", cliaddr.sin_addr.s_addr);

    #endif

    struct timeval t1, t2;

    // Start measurement routine
    while(1){

        // Start roundtrip measurement       
        msg[0] = 0x01;
        while (c1.ack == 0x00) //|| c2.ack == 0x00 || c3.ack == 0x00) //TODO: uncomment
        {
            gettimeofday(&t1, NULL);
#ifdef CPP_CLIENT
            sendto(sockfd, (const char *)msg, SEND_BUFF_SIZE, MSG_CONFIRM, (const struct sockaddr *) &cliaddr2, len);
#else
            sendto(sockfd, (const char *)msg, SEND_BUFF_SIZE, MSG_CONFIRM, (const struct sockaddr *) &cliaddr, len);
#endif
            n = recvfrom(sockfd, (char *)buffer, REC_BUFF_SIZE, MSG_WAITALL, NULL, NULL);
            printf("Sent message and received %d bytes.\n", n);
            printf("Received: 0x %02x %02x %02x %02x %02x\n", buffer[0], buffer[1], buffer[2], buffer[3], buffer[4]);
            gettimeofday(&t2, NULL);
            if (buffer[0] == (c1.ID << 4 | 0x02)) {
                c1.round_time = (t2.tv_sec * 1E6 + t2.tv_usec) - (t1.tv_sec * 1E6 + t1.tv_usec);
                c1.ack = 0x01;
                printf("C1 round trip measurement done!\n");
            }
            else if (buffer[0] == c2.ID) {
                c2.round_time = (t2.tv_sec * 1E6 + t2.tv_usec) - (t1.tv_sec * 1E6 + t1.tv_usec);
                c2.ack = 0x01;
            }
            else if (buffer[0] == c3.ID) {
                c3.round_time = (t2.tv_sec * 1E6 + t2.tv_usec) - (t1.tv_sec * 1E6 + t1.tv_usec);
                c3.ack = 0x01;
            }
        }

        // Broadcast signal to start measurement
        msg[0] = 0x02;
#ifdef CPP_CLIENT
        sendto(sockfd, (const char *)msg, SEND_BUFF_SIZE, MSG_CONFIRM, (const struct sockaddr *) &cliaddr2, len);
#else
        sendto(sockfd, (const char *)msg, SEND_BUFF_SIZE, MSG_CONFIRM, (const struct sockaddr *) &cliaddr, len);
#endif

        printf("Start measurement sent!\n");

        // Wait X seconds
        //sleep(2);

        // Play audio
        playAudio();

        // If received -> Calc results; if not -> Display error
        //float speedOfSound = 343.2; // 343.2 m/s

        printf("Terminating...\n");
        break;
    }
    
    return 0;
}
