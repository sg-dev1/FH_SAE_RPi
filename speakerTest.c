<<<<<<< HEAD
//#include <stdint.h>
#include <pigpio.h>
//#include <bcm2835.h>
#include <unistd.h>
#define SPEAKER_PIN 12
=======
#include <wiringPi.h>

#define PIN_LED 7
>>>>>>> ccb135b424b9f2883a5938eb1054032225a73254

int main() {
    if(wiringPiSetup() == -1) {
        return 1;
    }

    pinMode(PIN_LED, OUTPUT);

    while(1) {
	for(int i = 0; i < 5; i++)
	{
        digitalWrite(PIN_LED, 1);
        delay(5);
        digitalWrite(PIN_LED, 0);
	delay(5);
	}
	delay(1000);
    }
    return 0;
}
