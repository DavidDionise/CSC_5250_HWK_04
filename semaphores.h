#ifndef SEMAPHORES_H
#define SEMAPHORES_H

#include "data_structures.h"
#include "util.h"

int CHAIR_SEM = 0;
int SOFA_SEM = 0;
int STANDING_SEM = 0;
int REG_SEM = 0;


void chairWait(customer *customer);

void chairSignal();

void sofaWait(customer* customer);

void sofaSignal();

void standingWait(customer* customer);

void standingSignal();

void registerWait(barber *barber);

void registerSignal();


#endif
