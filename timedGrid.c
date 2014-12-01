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
			//display grid and increment
			displayGRID(tid);
			iteration ++;
			//determine whether or not the grid is stable
			pthread_mutex_lock(&gridsim.stable_lock);
			gridsim.stable = isStable(gridsim.sgrid);
			if(gridsim.stable==0){	
				printf("the grid is stable after %d iterations\n", iteration);
			}
			pthread_mutex_unlock(&gridsim.stable_lock);
 		}
 		bar_wait(gridsim.barrier);
    }
    pthread_exit(NULL);
}


int main(int argc, char **argv){
	clock_t start = clock();
	int NUMT = 8;
	barrier_t barr;
	sandgrid_t sandgrid;
	int grains = 100;
	int gridW = 16;
	int gridH = 16;

	// char *test = "is this working?";
	grid_simulation_t *gsim =  (grid_simulation_t *)malloc(sizeof(grid_simulation_t));
	gridsim = *gsim;

	printf("Running: %dx%d grid, %d grains until stable, 10 timesteps per round with %d threads.\n", gridW, gridH, grains, NUMTHREADS);

	init_sandgrid(&sandgrid, gridW, gridH, grains);
	bar_init(&barr, NUMT);
	
	gridsim.sgrid = &sandgrid;
	gridsim.barrier = &barr;
	gridsim.stable = 1; //not stable
	gridsim.threads = (pthread_t *)malloc(sizeof(pthread_t)*NUMT);
	gridsim.mutex = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t)*(NUMT-1));

	for (int i = 0; i<(NUMT-1); i++){
		pthread_mutex_init(&gridsim.mutex[i], NULL);
	}

	pthread_mutex_init(&gridsim.stable_lock, NULL);

	for (int i = 0; i<(NUMT); i++){
		printf("creating pthread %i\n", i);
		pthread_create(&gridsim.threads[i], NULL, loop, (void *)i);
	}

	for (int i = 0; i<NUMT; i++){
		printf("joining pthread %d\n ", i);
		pthread_join(gridsim.threads[i], NULL);
	}

	clock_t end = clock();
    double cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
    printf("time taken: %f seconds\n", cpu_time_used);
    //display the grid, if you like visual_grid(gridsim.sgrid);

	pthread_exit(NULL);
	exit(0);

}