#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#include "customer_handlers.h"
#include "data_structures.h"
#include "semaphores.h"

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

	pthread_attr_t attr;

	if(pthread_attr_init(pthread_attr_t &attr) < 0) {
		perror("Error initializing threads");
		exit(1);
	}
	if(pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED) < 0) {
		perror("Error initializing threads");
		exit(1);
	}

	if(pthread_create(&barber_1_thread, &attr, &baker_routine, barber_1) < 0) {
		perror("Error creating thread");
		exit(1);
	}
	if(pthread_create(&barber_2_thread, &attr, &baker_routine, barber_2) < 0) {
		perror("Error creating thread");
		exit(1);
	}
	if(pthread_create(&barber_3_thread, &attr, &baker_routine, barber_3) < 0) {
		perror("Error creating thread");
		exit(1);
	}

	while(COUNTER < time_limit) {
		handleNewMinute();
	}

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

	int i;
	for(i = 0; i < 3; i++) {
		if(barbers_array[i].cutting) {
			barbers_array[i].cutting_time++;
			
			if(barbers_array[i].cutting_time >= 5) {
				barbers_array[i].cutting = 0;

				sleeping_barber = findSleepingBarber();
				if(sleeping_barber) {
					registerWait(sleeping_barber);

					barbers_array[i].sleeping = 1;
					barbers_array[i].cutting = 0;
					barbers_array[i].waiting = 0;
					barbers_array[i].accepting_payment = 0;
				}
				else {
					registerWait(&barbers_array[i]);
				}
			}
			else if(barbers_array[i].accepting_payment) {
				barbers_array[i].accepting_time++;

				if(barbers_array[i].accepting_time >= 2) {
					barbers_array[i].cutting;
					barbers_array[i].sleeping;
					barbers_array[i].accepting_payment;
					barbers_array[i].waiting;

					registerSignal();
				}
			}
		}
	}
}
