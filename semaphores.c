#ifndef SEMAPHORES_H
#define SEMAPHORES_H

#include "data_structures.h"
#include "customer_handlers.h"

int CHAIR_SEM = 3;
int SOFA_SEM = 4;
int STANDING_SEM = 7;
int REG_SEM = 1;

void chairWait(customer *customer) {
	if(CHAR_SEM <= 3) {
		CHAR_SEM++;
		push(customer, &chair_queue);
	}
	else {
		sofaWait(customer);
	}
}

void chairSignal() {
	if(!isEmpty(&sofa_queue)) {
		push(sofa_queue.head, &chair_queue);
	}
		
	CHAR_SEM--;
}

void sofaWait(customer* customer) {
	SOFA_SEM++;
}

void sofaSignal() {
	SOFA_SEM--;
}

void standingWait(customer* customer) {
	STANDING_SEM++;
}

void standingSignal() {
	STANDING_SEM--;
}


#endif
