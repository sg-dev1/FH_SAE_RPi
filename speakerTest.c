//#include <stdint.h>
#include <pigpio.h>
//#include <bcm2835.h>
#include <unistd.h>
#define SPEAKER_PIN 12
#include <wiringPi.h>

#define PIN_LED 7

int main() {
    if(wiringPiSetup() == -1) {
        return 1;
    }

    pinMode(PIN_LED, OUTPUT);

    while(1) {
	for(int i = 0; i < 5; i++)
	{
        digitalWrite(PIN_LED, 1);
        delay(2);
        digitalWrite(PIN_LED, 0);
	    delay(2);
	}
	delay(1000);
    }
    return 0;
}
