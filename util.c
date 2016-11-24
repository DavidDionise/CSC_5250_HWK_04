#include "util.h"

void push(customer *customer, queue *queue) {
	if(queue->head == 0) {
		queue->head = customer;
		queue->tail = customer;
	}
	else {
		customer->next = queue->tail;
		queue->tail->prev = customer;
		queue->tail = customer;
	}
}

void pop(queue *queue) {
	if(queue->head == queue->tail) {
		queue->head = 0;
		queue->tail = 0;
	}
	else {
		customer *temp = queue->head;
		queue->head = queue->head->prev;
		queue->head->next = 0;
	}
}

int isEmpty(queue *queue) {
	if(queue->head == 0)
		return 1;

	return 0;
}

void rejectCustomer(customer* customer) {
	free(customer);
	DROPPED_CUSTOMER_COUNT++;
}

barber * findSleepingBarber() {
	int i;
	for(i = 0; i < 3; i++) {
		if(barbers_array[i].sleeping) {
			return &barbers_array[i];
		}
	}
	return 0;
}

void * barberRoutine(void *arg) {
	barber *barber = (barber*)arg;

	if(barber->cutting) {
		barber->cutting_time++;

		if(barber->cutting_time >= 5) {
			barber *sleeping_barber = findSleepingBarber();

			if(sleeping_barber) {
				registerWait(sleeping_barber);

				barber->cutting = 0;
				barber->sleeping = 1;
				barber->accepting_payment = 0;
			}
			chairSignal();
		}
	}
	else if(barber->accepting_payment) {
		barber->accepting_time++;

		if(barber->accepting_time >= 2) {
			barber->cutting = 0;
			barber->sleeping = 1;
			barber->accepting_payment = 0;
		}
		registerSignal();
	}
	return NULL;
}










