
#include "semaphores.h"

void chairWait(customer *customer) {
	if(CHAR_SEM < 3) {
		CHAR_SEM++;
		push(customer, &chair_queue);
	}
	else {
		sofaWait(customer);
	}
}

void chairSignal() {
	if(!isEmpty(&sofa_queue)) {
		push(&(sofa_queue.head), &chair_queue);
		pop(&chair_queue);
		
		sofaSignal();
	}
		
	CHAR_SEM--;
}

void sofaWait(customer* customer) {
	if(SOFA_SEM < 4) {
		SOFA_SEM++;
		push(customer, &sofa_queue);
	}
	else {
		standingWait(customer);
	}
}

void sofaSignal() {
	if(!isEmpty(&standing_queue)) {
		push(&(standing_queue.head), &sofa_queue);	
		pop(&sofa_queue);

		standingSignal();
	}

	SOFA_SEM--;
}

void standingWait(customer* customer) {
	if(STANDING_SEM < 7) {
		STANDING_SEM++;
		push(customer, &standing_queue);
	}
	else {
		rejectCustomer(customer);
	}
}

void standingSignal() {
	pop(&standing_queue);
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
		barber->waiting = 1;
		barber->sleeping = 0;
		barber->cutting = 0;
		barber->accepting_payment = 0;

		push(barber, &register_queue);
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
	if(!isEmpty(&register_queue)) {
		(register_queue.head)->accepting_payment = 1;
		(register_queue.head)->waiting = 0
		;
		pop(&register_queue);
	}

	REG_SEM++;
}
