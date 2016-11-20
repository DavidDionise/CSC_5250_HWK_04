#ifndef CUSTOMER_HANDLERS_H
#define CUSTOMER_HANDLERS_H

#include "data_structures.h";

void push(customer *customer, queue *queue);

void pop(queue *queue);

void rejectCustomer(customer* customer);

#endif
