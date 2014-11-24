#ifndef __BARRIER_H
#define __BARRIER_H

#define NUMTHREADS (1)
typedef struct _barrier_t{
	int counter;
	pthread_cond_t last_thread;
	pthread_mutex_t mutex;
}_barrier_t;

int barrier_init(barrier_t *barrier, int NUMTHREADS);
int barrier_wait(barrier_t *barrier); 

#endif