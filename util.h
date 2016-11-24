#ifndef UTIL_H
#define UTIL_H

#include <stdlib.h>

#include "globals.h"
#include "data_structures.h"

void customer_push(customer *customer, customer_queue *queue);

void customer_pop(customer_queue *queue);

void barber_push(barber *barber, barber_queue *queue);

void barber_pop(barber_queue *queue);

int customerQueueEmpty(customer_queue *queue);

int barberQueueEmpty(barber_queue *queue);

void rejectCustomer(customer* customer);

barber * findSleepingBarber();

int customerQueueEmpty(customer_queue *queue);

void * barberRoutine(void *args);

#endif
