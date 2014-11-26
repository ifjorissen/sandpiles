/* 
   Isabella Jorissen
   Hw. 6
   Math 389
   11.16.14
 */


#include "header.h"

grid_simulation_t gridsim;
barrier_t barr;
// sandgrid_t sandy;

int main(int argc, char **argv){
	// pthread_t pt_data [NUMTHREADS];
	// barrier_t barr;
	char *test = "is this working?";
	grid_simulation_t *gridsim =  (grid_simulation_t *)malloc(sizeof(grid_simulation_t));

	// printf("Running: 51x51 grid, 5,0000 grains, 2,500 rounds with one thread.\n");
	// sandgrid_t *sgrid = init_sandgrid(51, 51);
	// pthread_create(&sgrid->threads, NULL, stabilize, sgrid);
	// printf("Took _____ seconds.\n");

	printf("Running: 51x51 grid, 5,0000 grains, 2,500 rounds with one thread.\n");
	sandgrid_t sandgrid;
	init_sandgrid(&sandgrid, 51, 51);
	// sandgrid_t *sandgrid_ptr = &sandgrid;

	// barrier_t *barr_ptr = &barr;
	bar_init(&barr, NUMTHREADS);

	gridsim->sgrid = &sandgrid;
	gridsim->barrier = &barr;
	gridsim->msg = test;

	//initialize threads
	for (int i = 0; i<NUMTHREADS; i++){
		pthread_create(&gridsim->threads[i], NULL, stabilize, (void *)i);
		// pthread_join(pt_data[i], NULL);
	}
	for (int i = 0; i<NUMTHREADS; i++){
		// pthread_create(&pt_data[i], NULL, stabilize, (void *)i);
		pthread_join(gridsim->threads[i], NULL);
	}

	exit(0);

}