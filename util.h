#ifndef UTIL_H
#define UTIL_H

#include "data_structures.h";

void push(customer *customer, queue *queue);

void pop(queue *queue);

void rejectCustomer(customer* customer);

#endif
