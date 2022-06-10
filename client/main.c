#include <stdio.h>
#include <string.h>
#include <pthread.h>

#include "../errorCode.h"
#include "../sharedFunctions.h"
#include "clientFunctions.h"

#include <wiringPi.h>

#define SPEAKER_PIN 7

void playAudio() {
	for(int i = 0; i < 5; i++) {
        digitalWrite(SPEAKER_PIN, 1);
        delay(5);
        digitalWrite(SPEAKER_PIN, 0);
	    delay(5);
	}
}


int main(int argc, char *argv[]) {

    // Init GPIO
    if(wiringPiSetup() == -1) {
        return 1;
    }
    pinMode(SPEAKER_PIN, OUTPUT);

    pthread_t thread_id_1;
    pthread_t thread_id_2;
    //TODO add PI 3
    //pthread_t thread_id_3;

    thread_data_t tdata_pi_1;
    tdata_pi_1.addr = 1;

    thread_data_t tdata_pi_2;
    tdata_pi_2.addr = 2;

    //TODO add PI 3
    //thread_data_t tdata_pi_3;
    //tdata_pi_2.addr = 3;

    int numberOfCurrentRetriesPi_1 = 0;
    int numberOfCurrentRetriesPi_2 = 0;
    //TODO add PI 3
    //int numberOfCurrentRetriesPi_3 = 0;
    while (numberOfCurrentRetriesPi_1 < MAX_NUMBER_OF_RETRIES && numberOfCurrentRetriesPi_2 < MAX_NUMBER_OF_RETRIES) {

        //TODO probably not needed, PIs are sending the measured time difference
        unsigned long long timeStamp = current_timestamp();

        printf("NEW MEASUREMENT ***************************************************************************\n");
        printf("Current time: %llu\n", timeStamp);

        playAudio();

        pthread_create(&thread_id_1, NULL, connectToPi, (void *) &tdata_pi_1);
        pthread_create(&thread_id_2, NULL, connectToPi, (void *) &tdata_pi_2);
        //TODO add PI 3
        //pthread_create(&thread_id_3, NULL, connectToPi, (void *)&tdata_pi_3);

        pthread_join(thread_id_1, NULL);
        pthread_join(thread_id_2, NULL);
        //TODO add PI 3
        //pthread_join(thread_id_3, NULL);

        printf("After Thread*************************************************\n");

        printf("After Thread tdata.result_1: %llu\n", tdata_pi_1.result);
        printf("After Thread tdata.result_2: %llu\n", tdata_pi_2.result);

        //TODO add 3 PI and calculate distance
        if (tdata_pi_1.result != 0 && tdata_pi_2.result != 0) {
            printf("PI1 measured: %llu\n", tdata_pi_1.result);
            printf("PI2 measured: %llu\n", tdata_pi_2.result);
            //TODO add PI 3
//            printf("PI3 measured: %llu\n", tdata_pi_3.result);
            numberOfCurrentRetriesPi_1 = 0;
            numberOfCurrentRetriesPi_2 = 0;
            //TODO add PI 3
            //numberOfCurrentRetriesPi_3 = 0;
        } else {
            if(tdata_pi_1.result == 0) {
                numberOfCurrentRetriesPi_1++;
                printInsufficientDataError(numberOfCurrentRetriesPi_1, INSUFFICIENT_DATA_PI_1);
            }
            if(tdata_pi_2.result == 0) {
                numberOfCurrentRetriesPi_2++;
                printInsufficientDataError(numberOfCurrentRetriesPi_2, INSUFFICIENT_DATA_PI_2);
            }
            //TODO add PI 3
//            if(tdata_pi_3.result == 0) {
//                  numberOfCurrentRetriesPi_3++;
//                printInsufficientDataError(&numberOfCurrentRetriesPi_3, INSUFFICIENT_DATA_PI_3);
//            }

            if(numberOfCurrentRetriesPi_1 >= MAX_NUMBER_OF_RETRIES) {
                printError(PERMANENT_ERROR_PI_1);
            }
            if(numberOfCurrentRetriesPi_2 >= MAX_NUMBER_OF_RETRIES) {
                printError(PERMANENT_ERROR_PI_2);
            }
            //TODO add PI 3
//            if(numberOfCurrentRetriesPi_3 >= MAX_NUMBER_OF_RETRIES) {
//                printError(PERMANENT_ERROR_PI_3);
//            }
            //TODO add PI 3
            if(numberOfCurrentRetriesPi_1 >= MAX_NUMBER_OF_RETRIES || numberOfCurrentRetriesPi_2 >= MAX_NUMBER_OF_RETRIES) {
                break;
            }

            //printf("\nRetry %d / %d\n", numberOfCurrentRetriesPi_1, (MAX_NUMBER_OF_RETRIES - 1));
        }
    }
}