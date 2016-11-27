#ifndef GLOBALS_H
#define GLOBALS_H

// ***** BARBER STATUS ****** //

#define CUTTING 1000
#define SLEEPING 1001
#define ACCEPTING 1010
#define WAITING 1011

// ***** GLOBALS ****** //

extern int COUNTER;
extern int CUSTOMERS_IN_SHOP;
extern int SUCCESSFUL_CUSTOMER_COUNT;
extern int DROPPED_CUSTOMER_COUNT;

// ***** SEMAPHORES ****** //

extern int CHAIR_SEM;
extern int SOFA_SEM;
extern int STANDING_SEM;
extern int REG_SEM;

#endif
