
#include "semaphores.h"


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
		if(barbers_array[i].accepting_payment) {
			barbers_array[i].accepting_payment = 0;
			barbers_array[i].sleeping = 1;
			barbers_array[i].cutting = 0;

			break;
		}
	}
	if(!barberQueueEmpty(&register_queue)) {
		(register_queue.head)->accepting_payment = 1;
		
		barber_pop(&register_queue);
	}
	REG_SEM++;
}
