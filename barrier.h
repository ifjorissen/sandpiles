#ifndef __BARRIER_H
#define __BARRIER_H

// #define NUMTHREADS (1)

typedef struct _barrier_t{
	int counter;
	int c_max;
	pthread_cond_t last_thread;
	pthread_mutex_t mutex;
}barrier_t;

int barrier_init(barrier_t *barrier, int pt_num);
int barrier_wait(barrier_t *barrier); 

#endif