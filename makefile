
all:
	gcc -g data_structures.h semaphores.h semaphores.c util.h util.c main.c -pthread
