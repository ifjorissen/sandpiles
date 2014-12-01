/* 
   Isabella Jorissen
   Hw. 6
   Math 389
   11.16.14
 */

#include "header.h"

void *bar_init(barrier_t *barrier, int pt_num){
	pthread_cond_t last_thread;
	pthread_mutex_init(&barrier->mutex, NULL);
	pthread_cond_init(&barrier->last_thread, NULL);
	barrier->count = pt_num;
	barrier->capacity = pt_num;
	return NULL;
}

void *bar_wait(barrier_t *barrier){
	pthread_mutex_lock(&barrier->mutex);
	barrier->count--;
	if (barrier->count == 0){
		barrier->count = barrier->capacity;
		// printf("barrier met\n");
		pthread_cond_broadcast(&barrier->last_thread);
	}
	else{
		pthread_cond_wait(&barrier->last_thread, &barrier->mutex);	
	}
	pthread_mutex_unlock(&barrier->mutex);
	return NULL;
}