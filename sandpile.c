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
	barrier_t barr;
	sandgrid_t sandgrid;
	int grains = 100;
	int gridW = 16;
	int gridH = 16;

	// char *test = "is this working?";
	grid_simulation_t *gsim =  (grid_simulation_t *)malloc(sizeof(grid_simulation_t));

	printf("Running: %dx%d grid, %d grains until stable, 10 timesteps per round with four threads.\n", gridW, gridH, grains);

	init_sandgrid(&sandgrid, gridW, gridH, grains);
	bar_init(&barr, NUMTHREADS);

	gsim->sgrid = &sandgrid;
	gsim->barrier = &barr;
	gsim->stable = 1; //not stable

	gridsim = *gsim;

	for (int i = 0; i<(NUMTHREADS-1); i++){
		pthread_mutex_init(&gridsim.mutex[i], NULL);
	}

	pthread_mutex_init(&gridsim.stable_lock, NULL);

	for (int i = 0; i<(NUMTHREADS); i++){
		printf("creating pthread %i\n", i);
		pthread_create(&gridsim.threads[i], NULL, loop, (void *)i);
	}

	for (int i = 0; i<NUMTHREADS; i++){
		printf("joining pthread %d\n ", i);
		pthread_join(gridsim.threads[i], NULL);
	}

	clock_t end = clock();
    double cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
    printf("time taken: %f seconds\n", cpu_time_used);

	pthread_exit(NULL);
	exit(0);

}