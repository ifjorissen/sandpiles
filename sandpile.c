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
	int stable = 1;


	//initialize mutexes
	while(stable !=0){
		visual_grid(gridsim.sgrid);
		for (int i = 0; i<(NUMTHREADS-1); i++){
			pthread_mutex_init(&gridsim.mutex[i], NULL);
		}
		//initialize threads
		for (int i = 0; i<NUMTHREADS; i++){
			pthread_create(&gridsim.threads[i], NULL, stabilize, (void *)i);
		}
		//join threads
		for (int i = 0; i<NUMTHREADS; i++){
			pthread_join(gridsim.threads[i], NULL);
			// printf("region %d stable (0 if yes): %d\n", i, gridsim.stable_regions[i]);
		}
		stable = isStable(gridsim.sgrid);
	}

	//ascii visualization
	printf("Sandpile after stability has been reached: \n");
	visual_grid(gridsim.sgrid);

	exit(0);

}