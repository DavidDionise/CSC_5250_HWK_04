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
		if(barbers_array[i]->status == SLEEPING) {
			return barbers_array[i];
		}
	}
	return 0;
}

void * barberRoutine(void *arg) {
	barber *barber = (struct barber*)arg;

	if(barber->status == CUTTING) {
		barber->cutting_time++;

		if(barber->cutting_time > 5) {
			barber->cutting_time = 0;

			struct barber *sleeping_barber = findSleepingBarber();

			if(sleeping_barber) {
				registerWait(sleeping_barber);

				barber->status = SLEEPING;
			}
			else {
				registerWait(barber);
			}
		}
	}
	else if(barber->status == ACCEPTING) {
		barber->accepting_time++;

		if(barber->accepting_time > 2) {
			barber->accepting_time = 0;

			registerSignal();
			chairSignal();
		}
	}
	else if(barber->status == SLEEPING) {
		if(!customerQueueEmpty(&sofa_queue)) {
			barber->status = CUTTING;

			barber->current_customer = sofa_queue.tail;
			customer_pop(&sofa_queue);
			sofaSignal();
		}	
	}
	return NULL;
}

void printResults() {
	int sofa_customers = 0;
	int barber_chair_customers = 0;

	// Get number of customers seated on sofa and barber chairs
	customer *current;

	current = sofa_queue.head;
	while(current) {
		sofa_customers++;
		current = current->next;
	}

	current = barber_chair_queue.head;
	while(current) {
		barber_chair_customers++;
		current = current->next;
	}

	printf("Customers in shop : %i\n", CUSTOMERS_IN_SHOP);
	printf("Customers seated on sofa : %i\n", sofa_customers);
	printf("Customers seated on barber chairs : %i\n", barber_chair_customers);

	int i;
	for(i = 0; i < 3; i++) {
		printf("%s ", barbers_array[i]->name);

		if(barbers_array[i]->status == CUTTING) {
			puts("is cutting");
		}
		else if(barbers_array[i]->status == ACCEPTING) {
			puts("is accepting payment");
		}
		else if(barbers_array[i]->status == SLEEPING) {
			puts("is sleeping");
		}
		else if(barbers_array[i]->status == WAITING) {
			puts("is waiting at the register");
		}
	}

	printf("%i customers were dropped\n", DROPPED_CUSTOMER_COUNT);
}

// *********** SEMAPHORE FUNCTION ************ //

void chairWait(customer *customer) {
	if(CHAIR_SEM < 3) {
		CHAIR_SEM++;

		barber *sleeping_barber = findSleepingBarber();

		sleeping_barber->status = CUTTING;

		if(customer->number == 0) {
			CUSTOMERS_IN_SHOP++;
			customer->number = CUSTOMERS_IN_SHOP;
			customer_push(customer, &barber_chair_queue);
		}

		sleeping_barber->current_customer = customer;
	}
	else {
		sofaWait(customer);
	}
}

void chairSignal() {
	if(!customerQueueEmpty(&sofa_queue)) {
		customer_pop(&barber_chair_queue);

		chairWait(sofa_queue.head);
		customer_pop(&sofa_queue);
	}
	CUSTOMERS_IN_SHOP--;
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

		barber->status = ACCEPTING;
	}
	else {
		barber->status = WAITING;

		barber_push(barber, &register_queue);
	}
}

void registerSignal() {
	int i;
	for(i = 0; i < 3; i++) {
		if(barbers_array[i]->status == ACCEPTING) {
			if(!customerQueueEmpty(&sofa_queue)) {
				barbers_array[i]->status = CUTTING;
				barbers_array[i]->current_customer = sofa_queue.head;
				customer_pop(&sofa_queue);
			}
			barbers_array[i]->status = SLEEPING;

			break;
		}
	}
	if(!barberQueueEmpty(&register_queue)) {
		register_queue.head->status = ACCEPTING;
		
		barber_pop(&register_queue);
	}
	REG_SEM--;
}


// int main() {
// 	return 0;
// }

