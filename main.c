#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#include "util.h"

void handleNewMinute();

int main(int argc, char *argv[]) {
	if(argc < 2) {
		perror("Must include a time limit");
		exit(1);
	}

	int time_limit = atoi(argv[1]);

	// Initialze barber threads
	pthread_t barber_1_thread;
	pthread_t barber_2_thread;
	pthread_t barber_3_thread;

	void *barber_1 = barbers_array[0];
	void *barber_2 = barbers_array[1];
	void *barber_3 = barbers_array[2];

	while(COUNTER < time_limit) {
		handleNewMinute();
	}

	printResults();

	return 0;
}

void handleNewMinute() {
	COUNTER++;
	barber *sleeping_barber;

	if(COUNTER % 3 == 0) {
		customer *new_customer = malloc(sizeof(customer));
		new_customer->cut_time = 0;
		new_customer->next = 0;
		new_customer->prev = 0;

		chairWait(new_customer);
	}

	if(pthread_create(&barber_1_thread, &attr, &barberRoutine, barber_1) < 0) {
		perror("Error creating thread");
		exit(1);
	}
	if(pthread_create(&barber_2_thread, &attr, &barberRoutine, barber_2) < 0) {
		perror("Error creating thread");
		exit(1);
	}
	if(pthread_create(&barber_3_thread, &attr, &barberRoutine, barber_3) < 0) {
		perror("Error creating thread");
		exit(1);
	}

	if(pthread_join(&barber_1_thread, NULL) < 0) {
		perror("Error joining thread");
		exit(1);
	}
	if(pthread_join(&barber_2_thread, NULL) < 0) {
		perror("Error joining thread");
		exit(1);
	}
	if(pthread_join(&barber_3_thread, NULL) < 0) {
		perror("Error joining thread");
		exit(1);
	}
}

void printResults() {
	int i;
	for(i = 0; i < 3; i++) {
		printf("%s ", barber[i]->name);

		if(barber[i]->cutting) {
			puts("is cutting");
		}
		else if(barber[i]->accepting payment) {
			puts("is accepting payment");
		}
		else(barber[i]->sleeping) {
			puts("is sleeping");
		}
	}
}
