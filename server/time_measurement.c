#include "time_measurement.h"

#include <stdio.h>

#define PIN RPI_BPLUS_GPIO_J8_05

static void measurementinterrupt(TimeMeasurement *meas);

void init_time_measurement(TimeMeasurement *meas) {
	    //Init GPIO 
    if(!bcm2835_init())
        printf("Failed Init\n");
    bcm2835_gpio_fsel(PIN, BCM2835_GPIO_FSEL_INPT);
    bcm2835_gpio_set_pud(PIN, BCM2835_GPIO_PUD_DOWN);

    //Time GPIO
    meas->values.start.tv_sec  = 0;
    meas->values.start.tv_nsec = 0;
    meas->values.end.tv_sec  = 0;
    meas->values.end.tv_nsec = 0;

    meas->time_delay_comm   = 0;
    meas->time_delay_master = 0;

    meas->initialized = 1;
}

uint32_t measurement(TimeMeasurement *meas) {
	if (!DEBUG)
    {
        struct timespec time;
        clock_gettime(CLOCK_REALTIME, &time);
        meas->values.start = time; 
        bcm2835_gpio_hen(PIN);
        while(1)
        {
            if(bcm2835_gpio_eds(PIN))
            {
                measurementinterrupt(meas);
                bcm2835_gpio_set_eds(PIN);
                break;
            }
        }
        //Measured time calc - prototype // nano seconfs
        meas->values.elapsed = ((meas->values.start.tv_sec * 1000000L) + meas->values.start.tv_nsec/1000) - ((meas->values.end.tv_sec * 1000000L) + meas->values.end.tv_nsec/1000);

        return meas->values.elapsed;
    }
    else
    {
        uint32_t debug = 0x55555555;
        return debug;
    }
}

static void measurementinterrupt(TimeMeasurement *meas)
{
    struct timespec time;
    clock_gettime(CLOCK_REALTIME, &time);
    meas->values.end = time;
}
