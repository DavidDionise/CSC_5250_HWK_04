#ifndef DATA_STRUCTURES_H
#define DATA_STRUCTURES_H

typedef struct customer {
	int number;
	struct customer *next;
	struct customer *prev;
} customer;

typedef struct barber {
	char *name;
	int cutting_time;
	int accepting_time;
	int status;

	struct barber *next;

	customer *current_customer;
} barber;

typedef struct customer_queue {
	customer *head;
	customer *tail;
} customer_queue;

typedef struct barber_queue {
	barber *head;
	barber *tail;
} barber_queue;

// Declare structs
struct barber barber_1;
struct barber barber_2;
struct barber barber_3;

struct customer_queue barber_chair_queue; 
struct customer_queue sofa_queue;
struct customer_queue standing_queue;
struct barber_queue register_queue;

barber* barbers_array[3];

#endif
