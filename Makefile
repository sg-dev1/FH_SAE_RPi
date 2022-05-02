all: client master

client: client.c settings.h
	gcc client.c -Wall -Wextra -o client

master: main_master.c settings.h
	gcc main_master.c -Wall -Wextra -o master 