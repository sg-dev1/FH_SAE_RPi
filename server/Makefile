all: server

server: main.c
	gcc -Wall -o server main.c time_measurement.c time_measurement.h ../errorCode.c ../errorCode.h ../sharedFunctions.c ../sharedFunctions.h -pthread -L../bcm2835-1.71/src/ -lbcm2835 -I../bcm2835-1.71/src
