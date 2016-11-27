#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#include "util.h"

void handleNewMinute(pthread_t *barber_1_thread, pthread_t *barber_2_thread,
	pthread_t *barber_3_thread);

void printResults();

int main(int argc, char *argv[]) {
	if(argc < 2) {
		perror("Must include a time limit");
		exit(1);
	}

	// Declare structs
	struct barber barber_1;
	struct barber barber_2;
	struct barber barber_3;

	struct customer_queue chair_queue;
	struct customer_queue sofa_queue;
	struct customer_queue standing_queue;
	struct barber_queue register_queue;

	// Initialize barbers
	puts("hit");
	barber_1.name = "Barber 1";
	barber_1.cutting = 0;
	barber_1.sleeping = 1;
	barber_1.accepting_payment = 0;
	barber_1.current_customer = 0;
puts("hit");
	barber_2.name = "Barber 2";
	barber_2.cutting = 0;
	barber_2.sleeping = 1;
	barber_2.accepting_payment = 0;
	barber_2.current_customer = 0;
puts("hit");
	barber_3.name = "Barber 3";
	barber_3.cutting = 0;
	barber_3.sleeping = 1;
	barber_3.accepting_payment = 0;
	barber_3.current_customer = 0;
puts("hit");
	barbers_array[0] = &barber_1;
	barbers_array[1] = &barber_2;
	barbers_array[2] = &barber_3;
puts("hit");
	// Initialize queue's
	chair_queue.head = 0;
	chair_queue.tail = 0;
	sofa_queue.head = 0;
	sofa_queue.tail = 0;
	standing_queue.head = 0;
	standing_queue.tail = 0;
	register_queue.head = 0;
	register_queue.tail = 0;
puts("hit");
	int time_limit = atoi(argv[1]);
puts("hit");
	// Initialze barber threads
	pthread_t barber_1_thread;
	pthread_t barber_2_thread;
	pthread_t barber_3_thread;
puts("hit");
	while(COUNTER < time_limit) {
		handleNewMinute(&barber_1_thread, &barber_2_thread, 
			&barber_3_thread);
	}

	printResults();

	return 0;
}

void handleNewMinute(pthread_t *barber_1_thread, pthread_t *barber_2_thread,
	pthread_t *barber_3_thread) {
puts("hit");
	COUNTER++;
	barber *sleeping_barber;

	if(COUNTER % 3 == 0) {
		customer *new_customer = malloc(sizeof(customer));
		new_customer->number = 0;
		new_customer->next = 0;
		new_customer->prev = 0;

		chairWait(new_customer);
	}
puts("hit");
	if(pthread_create(barber_1_thread, NULL, &barberRoutine, (void*)barbers_array[0]) < 0) {
		perror("Error creating thread");
		exit(1);
	}
	if(pthread_create(barber_2_thread, NULL, &barberRoutine, (void*)barbers_array[1]) < 0) {
		perror("Error creating thread");
		exit(1);
	}
	if(pthread_create(barber_3_thread, NULL, &barberRoutine, (void*)barbers_array[2]) < 0) {
		perror("Error creating thread");
		exit(1);
	}
puts("hit");
	if(pthread_join(*barber_1_thread, NULL) < 0) {
		perror("Error joining thread");
		exit(1);
	}
	if(pthread_join(*barber_2_thread, NULL) < 0) {
		perror("Error joining thread");
		exit(1);
	}
	if(pthread_join(*barber_3_thread, NULL) < 0) {
		perror("Error joining thread");
		exit(1);
	}
}

void printResults() {
	int i;
	for(i = 0; i < 3; i++) {
		printf("%s ", barbers_array[i]->name);

		if(barbers_array[i]->cutting) {
			puts("is cutting");
		}
		else if(barbers_array[i]->accepting_payment) {
			puts("is accepting payment");
		}
		else if(barbers_array[i]->sleeping) {
			puts("is sleeping");
		}
	}
}
