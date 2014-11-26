/* 
   Isabella Jorissen
   Hw. 6
   Math 389
   11.16.14
 */

#include "header.h"

void *bar_init(barrier_t *barrier, int pt_num){
	printf("barrier initialized with %d threads.\n", pt_num);
	pthread_cond_t last_thread;
	pthread_mutex_init(&barrier->mutex, NULL);
	pthread_cond_init(&barrier->last_thread, NULL);
	barrier->cmax = pt_num;
	barrier->count = 0;
	return NULL;
}

void *bar_wait(barrier_t *barrier){
	printf("barrier wait called, capacity: %d\n", barrier->cmax);
	pthread_mutex_lock(&barrier->mutex);
	printf("mutex locked\n");
	barrier->count++;
	if (barrier->count == barrier->cmax){
		barrier->count = 0;

		pthread_cond_broadcast(&barrier->last_thread);
		pthread_mutex_unlock(&barrier->mutex);
		printf("condition met, mutex unlocked\n");
	}
	else{
		printf("waiting count = %d\n", barrier->count);
		pthread_cond_wait(&barrier->last_thread, &barrier->mutex);	
	}
	pthread_mutex_unlock(&barrier->mutex);
	return NULL;
}