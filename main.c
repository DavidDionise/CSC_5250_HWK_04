#include "customer_handlers.h"
#include "data_structures.h"
#include "semaphores.h"

void handleNewMinute();

int main(int argc, char *argv[]) {
	if(argc < 2) {
		perror("Must include a time limit");
		exit(1);
	}

	int time_limit = atoi(argv[1]);


	return 0;
}

void handleNewMinute() {
	COUNTER++;
	barber *sleeping_barber;

	if(COUNTER % 3 == 0) {
		customer *new_customer = malloc(sizeof(customer));
		new_customer->cut_time = 0;
		new_customer->next = 0;
		new_customer->prev = 0;

		chairWait(new_customer);
	}


	int i;
	for(i = 0; i < 3; i++) {
		if(barbers_array[i].cutting) {
			barbers_array[i].cutting_time++;
			
			if(barbers_array[i].cutting_time >= 5) {
				barbers_array[i].cutting = 0;
				registerWait(&barbers_array[i]);

				sleeping_barber = findSleepingBarber();
				if(sleeping_barber) {
					registerWait(sleeping_barber);
				}
				else {
					registerWait(&barbers_array[i]);
				}
			}
		}
	}
}
