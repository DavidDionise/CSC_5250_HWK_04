#ifndef UTIL_H
#define UTIL_H

#include "semaphores.h"

void push(customer *customer, queue *queue);

void pop(queue *queue);

void rejectCustomer(customer* customer);

barber * findSleepingBarber();

void * barberRoutine(void *args);

#endif
