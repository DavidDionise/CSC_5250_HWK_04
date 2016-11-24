#ifndef SEMAPHORES_H
#define SEMAPHORES_H

#include "data_structures.h"

int COUNTER = 0;
int DROPPED_CUSTOMER_COUNT = 0;

int CHAIR_SEM = 3;
int SOFA_SEM = 4;
int STANDING_SEM = 7;
int REG_SEM = 1;

void chairWait(customer *customer);

void chairSignal();

void sofaWait(customer* customer);

void sofaSignal();

void standingWait(customer* customer);

void standingSignal();

void registerWait(barber *barber);

void registerSignal();


#endif
