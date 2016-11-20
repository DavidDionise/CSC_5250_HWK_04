#ifndef DATA_STRUCTURES_H
#define DATA_STRUCTURES_H

struct customer {
	int cut_time;

	customer *next;
	customer *prev;
};

struct queue {
	customer *head;
	customer *tail;
};

// Declare structs
struct customer customer;
struct queue chair_queue;
struct queue sofa_queue;
struct queue standing_queue;
struct queue register_queue;

#endif
