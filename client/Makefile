all: client master

master: main.c
	gcc -o master main.c clientFunctions.c clientFunctions.h ../errorCode.c ../errorCode.h ../sharedFunctions.c ../sharedFunctions.h -pthread -lwiringPi