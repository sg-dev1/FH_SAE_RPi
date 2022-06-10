#include <stdio.h>
#include "errorCode.h"
#include "sharedFunctions.h"

/**
 * brief prints error codes
 * @param errorCode the actual error that occurred
 */
void printError(errorCode_t errorCode) {
    if(errorCode == BIND_ERROR) {
        printf("Can't Bind to address.\n");
    }
    if(errorCode == BIND_ERROR) {
        printf("Can't listen to address.\n");
    }
    if(errorCode == SOCKET_ERROR) {
        printf("Socket creation failed.\n");
    }
    if(errorCode == READ_ERROR) {
        printf("READ function error.\n");
    }
    if(errorCode == INET_ADDR_ERROR) {
        printf("Can't create IP Address.\n");
    }
    if(errorCode == SEND_ERROR) {
        printf("send function failed.\n");
    }
    if(errorCode == RECEIVE_ERROR) {
        printf("receive function failed.\n");
    }
    if(errorCode == TIMEOUT_REACHED) {
        printf("TIMEOUT reached. Server not responding...giving up...\n");
    }
    if(errorCode == INVALID_IP_ADDRESS) {
        printf("Invalid IP address passed.\n");
    }
    if(errorCode == INSUFFICIENT_DATA_PI_1) {
        printf("Can't calculate result. Insufficient Data from PI 1. ");
    }
    if(errorCode == INSUFFICIENT_DATA_PI_2) {
        printf("Can't calculate result. Insufficient Data from PI 2. ");
    }
    if(errorCode == INSUFFICIENT_DATA_PI_3) {
        printf("Can't calculate result. Insufficient Data from PI 3. ");
    }
    if(errorCode == PERMANENT_ERROR_PI_1) {
        printf("Wasn't able to collect data. PI 1 wasn't reachable.\n");
    }
    if(errorCode == PERMANENT_ERROR_PI_2) {
        printf("Wasn't able to collect data. PI 2 wasn't reachable.\n");
    }
    if(errorCode == PERMANENT_ERROR_PI_3) {
        printf("Wasn't able to collect data. PI 3 wasn't reachable.\n");
    }
}

void printInsufficientDataError(int numberOfCurrentRetriesPi_X, int errorEnum) {
    //(*numberOfCurrentRetriesPi_X)++;
    printError(errorEnum);
    if(numberOfCurrentRetriesPi_X <= 5) {
        printf("Retry %d / %d \n", numberOfCurrentRetriesPi_X, (MAX_NUMBER_OF_RETRIES - 1));
    }
}

//void printError(struct errorCode errorCode) {
//    if(errorCode.errorCause == BIND_ERROR) {
//        printf("Can't Bind to address.\n");
//    }
//    if(errorCode.errorCause == LISTEN_ERROR) {
//        printf("Can't listen to address.\n");
//    }
//    if(errorCode.errorCause == SOCKET_ERROR) {
//        printf("Socket creation failed.\n");
//    }
//    if(errorCode.errorCause == READ_ERROR) {
//        printf("READ function error.\n");
//    }
//    if(errorCode.errorCause == INET_ADDR_ERROR) {
//        printf("Can't create IP Address.\n");
//    }
//    if(errorCode.errorCause == SEND_ERROR) {
//        printf("send function failed.\n");
//    }
//    if(errorCode.errorCause == RECEIVE_ERROR) {
//        printf("receive function failed.\n");
//    }
//    if(errorCode.errorCause == TIMEOUT_REACHED) {
//        printf("TIMEOUT reached. Server not responding...giving up...\n");
//    }
//    if(errorCode.errorCause == INVALID_IP_ADDRESS) {
//        printf("Invalid IP address passed.\n");
//    }
//    if(errorCode.errorCause == INSUFFICIENT_DATA_PI_1) {
//        printf("Can't calculate result. Insufficient Data.\n");
//    }
//    if(errorCode.errorCause == PERMANENT_ERROR_PI_1) {
//        printf("Wasn't able to collect .\n");
//    }
//
//}

