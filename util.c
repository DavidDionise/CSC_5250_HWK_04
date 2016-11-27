#include "util.h"

void customer_push(customer *customer, customer_queue *queue) {
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

void customer_pop(customer_queue *queue) {
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

void barber_push(barber *barber, barber_queue *queue) {
	if(queue->head == 0) {
		queue->head = barber;
		queue->tail = barber;
	}
	else {
		barber->next = queue->tail;
		queue->tail = barber;
	}
}

void barber_pop(barber_queue *queue) {
	if(queue->head == queue->tail) {
		queue->head = 0;
		queue->tail = 0;
	}
	else {
		barber *temp = queue->head;
		queue->head->next = 0;
	}
}

int customerQueueEmpty(customer_queue *queue) {
	if(queue->head == 0)
		return 1;

	return 0;
}

int barberQueueEmpty(barber_queue *queue) {
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
		if(barbers_array[i]->sleeping) {
			return barbers_array[i];
		}
	}
	return 0;
}

void * barberRoutine(void *arg) {
	puts("hit");
	barber *barber = (struct barber*)arg;

	if(barber->cutting) {
		barber->cutting_time++;

		if(barber->cutting_time >= 5) {
			struct barber *sleeping_barber = findSleepingBarber();

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
	else if(barber->sleeping) {
		if(!customerQueueEmpty(&sofa_queue)) {
			barber->cutting = 1;
			barber->sleeping = 0;
			barber->accepting_payment = 0;

			barber->current_customer = sofa_queue.tail;
			customer_pop(&sofa_queue);
			sofaSignal();
		}	

	}
	return NULL;
}

// *********** SEMAPHORE FUNCTION ************ //

void chairWait(customer *customer) {
	if(CHAIR_SEM < 3) {
		CHAIR_SEM++;

		barber *sleeping_barber = findSleepingBarber();

		sleeping_barber->cutting = 1;
		sleeping_barber->sleeping = 0;
		sleeping_barber->accepting_payment = 0;

		if(customer->number == 0) {
			CUSTOMERS_IN_SHOP++;
			customer->number = CUSTOMERS_IN_SHOP;
		}

		sleeping_barber->current_customer = customer;
	}
	else {
		sofaWait(customer);
	}
}

void chairSignal() {
	if(!customerQueueEmpty(&sofa_queue)) {
		chairWait(sofa_queue.tail);
		customer_pop(&sofa_queue);
	}
	CHAIR_SEM--;
}

void sofaWait(customer* customer) {
	if(SOFA_SEM < 4) {
		SOFA_SEM++;

		if(customer->number == 0) {
			CUSTOMERS_IN_SHOP++;
			customer->number = CUSTOMERS_IN_SHOP;
		}

		customer_push(customer, &sofa_queue);
	}
	else {
		standingWait(customer);
	}
}

void sofaSignal() {
	if(!customerQueueEmpty(&standing_queue)) {
		customer_push(standing_queue.head, &sofa_queue);	
		customer_pop(&sofa_queue);

		standingSignal();
	}
	SOFA_SEM--;
}

void standingWait(customer* customer) {
	if(STANDING_SEM < 7) {
		STANDING_SEM++;

		if(customer->number == 0) {
			CUSTOMERS_IN_SHOP++;
			customer->number = CUSTOMERS_IN_SHOP;
		}

		customer_push(customer, &standing_queue);
	}
	else {
		rejectCustomer(customer);
	}
}

void standingSignal() {
	customer_pop(&standing_queue);
	STANDING_SEM--;
}

void registerWait(barber *barber) {
	if(REG_SEM < 1) {
		REG_SEM++;
		barber->accepting_payment = 1;
		barber->sleeping = 0;
		barber->cutting = 0;
	}
	else {
		barber->sleeping = 0;
		barber->cutting = 0;
		barber->accepting_payment = 0;

		barber_push(barber, &register_queue);
	}
}

void registerSignal() {
	int i;
	for(i = 0; i < 3; i++) {
		if(barbers_array[i]->accepting_payment) {
			barbers_array[i]->accepting_payment = 0;
			barbers_array[i]->sleeping = 1;
			barbers_array[i]->cutting = 0;

			break;
		}
	}
	if(!barberQueueEmpty(&register_queue)) {
		(register_queue.head)->accepting_payment = 1;
		
		barber_pop(&register_queue);
	}
	REG_SEM++;
}


// int main() {
// 	return 0;
// }

