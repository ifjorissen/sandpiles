/* 
   Isabella Jorissen
   Hw. 6
   Math 389
   11.16.14
 */


#include "header.h"

grid_simulation_t gridsim;


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
	// gsim->msg = test;

	gridsim = *gsim;

	//initialize mutexes
	for (int i = 0; i<(NUMTHREADS-1); i++){
		pthread_mutex_init(&gsim->mutex[i], NULL);
	}

	//initialize threads
	for (int i = 0; i<NUMTHREADS; i++){
		pthread_create(&gsim->threads[i], NULL, stabilize, (void *)i);
	}
	for (int i = 0; i<NUMTHREADS; i++){
		pthread_join(gsim->threads[i], NULL);
	}
	visual_grid(gridsim.sgrid);

	exit(0);

}