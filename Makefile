all: client master

client: client.c settings.h
	gcc client.c -Wall -Wextra -o client

master: main_master.c settings.h
	gcc main_master.c -o main

master_Wall: main_master.c settings.h
	     gcc main_master.c -Wall -Wextra -o main -lwiringPi

