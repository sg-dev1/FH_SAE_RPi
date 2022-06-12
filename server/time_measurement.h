#ifndef TIME_MEASUREMENT_H
#define TIME_MEASUREMENT_H

#define DEBUG 1u

#include <time.h>   //Time library 
#include <bcm2835.h> //GPIO lib

typedef struct{
    struct timespec start;
    struct timespec end; 
    uint32_t elapsed;
} measurement_struct; 

typedef struct {
    //Time delay on the communication
    long time_delay_comm;
    //Time delay to master cpu
    long time_delay_master; 
    //General indicator
    int initialized; 
    //Measurment
    measurement_struct values;
    
} TimeMeasurement;

void init_time_measurement(TimeMeasurement *meas);

uint32_t measurement(TimeMeasurement *meas);

#endif
