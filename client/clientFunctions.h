//
// Created by VolkerTenta on 06/06/2022.
//

#ifndef CLIENT_CLIENTFUNCTIONS_H
#define CLIENT_CLIENTFUNCTIONS_H

#define TIMEOUT 10 * 1000 /** Time the client will wait for response in milliseconds **/
#define MAX_CLIENTS 6 //TODO check if needed
#define MAX_BUFFER_SIZE 256


typedef struct thread_data {
    int addr;
    unsigned long long result;
} thread_data_t;

void* connectToPi(void* p_pi);

#endif //CLIENT_CLIENTFUNCTIONS_H
