#ifndef DATA_STRUCTURES_H
#define DATA_STRUCTURES_H

typedef struct customer {
	customer *next;
	customer *prev;
} customer;

typedef struct barber {
	char *name;

	int cutting_time;
	int accepting_time;

	int cutting;
	int sleeping;
	int accepting_payment;

	customer *current_customer;
} barber;

struct queue {
	customer *head;
	customer *tail;
};

// Declare structs
struct barber barber_1;
struct barber barber_2;
struct barber barber_3;

struct queue chair_queue;
struct queue sofa_queue;
struct queue standing_queue;
struct queue register_queue;

// Initialize barbers
barber_1.name = "Barber 1";
barber_1.cutting = 0;
barber_1.sleeping = 1;
barber_1.accepting_payment = 0;
barber_1.current_customer = 0;

barber_2.name = "Barber 2";
barber_2.cutting = 0;
barber_2.sleeping = 1;
barber_2.accepting_payment = 0;
barber_2.current_customer = 0;

barber_3.name = "Barber 3";
barber_3.cutting = 0;
barber_3.sleeping = 1;
barber_3.accepting_payment = 0;
barber_3.current_customer = 0;

struct barbers_array[3] = {barber_1, barber_2, barber_3};

// Initialize queue's
chair_queue.head = 0;
chair_queue.tail = 0;
sofa_queue.head = 0;
sofa_queue.tail = 0;
standing_queue.head = 0;
standing_queue.tail = 0;
register_queue.head = 0;
register_queue.tail = 0;


#endif
