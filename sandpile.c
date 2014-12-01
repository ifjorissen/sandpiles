/* 
   Isabella Jorissen
   Hw. 6
   Math 389
   11.16.14
 */


#include "header.h"
#include <time.h>

grid_simulation_t gridsim;

void *loop(void* info){
	int tid = (int) info;
	int iteration = 0;

    while (gridsim.stable != 0) {
		stabilize(tid);
		bar_wait(gridsim.barrier);
		if (tid == 0) {
			//display grid and increment mutex
			iteration ++;
			printf("\niteration: %d", iteration);
			displayGRID(tid);

			//determine whether or not the grid is stable
			//and update the variable
			pthread_mutex_lock(&gridsim.stable_lock);
			gridsim.stable = isStable(gridsim.sgrid);
			if(gridsim.stable==0){	
				printf("the grid is stable after %d iterations\n", iteration);
			}
			pthread_mutex_unlock(&gridsim.stable_lock);
 		}
 		bar_wait(gridsim.barrier);
 		printf("stable: %d tid: %d\n", gridsim.stable, tid );
    }
    pthread_exit(NULL);
}

int main(int argc, char **argv){
	clock_t start = clock();
	int thread_num = 4;
	barrier_t barr;
	sandgrid_t sandgrid;
	int grains = 100;
	int gridW = 16;
	int gridH = 16;

	grid_simulation_t *gsim =  (grid_simulation_t *)malloc(sizeof(grid_simulation_t));
	gridsim = *gsim;

	printf("Running: %dx%d grid, %d grains until stable, 10 timesteps per round with %d threads.\n", gridW, gridH, grains, thread_num);

	init_sandgrid(&sandgrid, gridW, gridH, grains);
	bar_init(&barr, thread_num);

	gridsim.sgrid = &sandgrid;
	gridsim.barrier = &barr;
	gridsim.stable = 1; //not stable
	gridsim.num_threads = thread_num;
	gridsim.threads = (pthread_t *)malloc(sizeof(pthread_t)*thread_num);
	gridsim.mutex = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t)*(thread_num-1));

	for (int i = 0; i<(thread_num-1); i++){
		pthread_mutex_init(&gridsim.mutex[i], NULL);
	}

	pthread_mutex_init(&gridsim.stable_lock, NULL);

	for (int i = 0; i<(thread_num); i++){
		printf("creating pthread %i\n", i);
		pthread_create(&gridsim.threads[i], NULL, loop, (void *)i);
	}

	for (int i = 0; i<thread_num; i++){
		printf("joining pthread %d\n ", i);
		pthread_join(gridsim.threads[i], NULL);
	}

	clock_t end = clock();
    double cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
    printf("time taken: %f seconds\n", cpu_time_used);

	pthread_exit(NULL);
	exit(0);

}