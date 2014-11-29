/* 
   Isabella Jorissen
   Hw. 6
   Math 389
   11.16.14
 */


#include "header.h"

grid_simulation_t gridsim;

void *loop(void* info){
	int tid = (int) info;
	int iteration = 0;
    while (1) {
		stabilize(tid);
		bar_wait(gridsim.barrier);
		if (tid == 0) {
			iteration ++;
			printf("\niteration: %d", iteration);
			displayGRID(tid);

			//determine whether or not the grid is stable
			pthread_mutex_lock(&gridsim.stable_lock);
			gridsim.stable = isStable(gridsim.sgrid);
			if(gridsim.stable==0){	
				printf("the grid is stable\n");
    			exit(0);
    			// pthread_mutex_unlock(&gridsim.stable_lock);
    			return NULL;
			}
			pthread_mutex_unlock(&gridsim.stable_lock);
 		}
 		bar_wait(gridsim.barrier);
 		printf("stable: %d tid: %d\n", gridsim.stable, tid );
    }
    // printf("the grid is stable\n");
    // // pthread_exit(0);
    // exit(0);
    return NULL;
}

int main(int argc, char **argv){
	barrier_t barr;
	sandgrid_t sandgrid;

	// char *test = "is this working?";
	grid_simulation_t *gsim =  (grid_simulation_t *)malloc(sizeof(grid_simulation_t));

	printf("Running: 64x64 grid, 5,0000 grains, 2,500 rounds with one thread.\n");

	init_sandgrid(&sandgrid, 16, 16);
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

	// for (int i = 0; i<NUMTHREADS; i++){
	// 	printf("joining pthread %d", i);
	// 	pthread_join(gridsim.threads[i], NULL);
	// }

	pthread_exit(NULL);
	exit(0);

}