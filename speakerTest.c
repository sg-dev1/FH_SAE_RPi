//#include <stdint.h>
#include <pigpio.h>
//#include <bcm2835.h>
#include <unistd.h>
#define SPEAKER_PIN 12

int main() {

    // RPi gpio init
    if (gpioInitialise()<0) {
        return 1;
    }

    gpioSetMode(PIN_LED, PI_OUTPUT);

    while (1) {
        // Play click
        gpioWrite(SPEAKER_PIN, 1);
        sleep(1);
        gpioWrite(SPEAKER_PIN, 0);
    }
}