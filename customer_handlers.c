#include "customer_handlers.h"

void push(customer *customer, queue *queue) {
	if(queue->head == 0) {
		queue->head = customer;
		queue->tail = customer;
	}
	else {
		queue->tail->prev = customer;
		customer->next = queue->tail;
		queue->tail = customer;
	}
}

void pop(queue *queue) {
	if(queue->head == queue->tail) {
		free(queue->head);
		queue->head = 0;
		queue->tail = 0;
	}
	else {
		customer *temp = queue->tail;
		queue->tail = temp->next;
		queue->tail->prev = 0;
		free(temp);
	}
}

int isEmpty(queue *queue) {
	if(queue->head == 0)
		return 1;

	return 0;
}

void rejectCustomer(customer* customer) {
	free(customer);
}
