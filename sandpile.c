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
		for (int i = 0; i<(NUMTHREADS-1); i++){
			pthread_mutex_init(&gridsim.mutex[i], NULL);
		}
		//initialize threads
		//initialize display thread
		printf("creating display thread\n");
		pthread_create(&gridsim.threads[NUMTHREADS-1], NULL, displayGRID, (void *)NUMTHREADS);
		stable = isStable(gridsim.sgrid);
		
		for (int i = 0; i<(NUMTHREADS-1); i++){
			pthread_create(&gridsim.threads[i], NULL, stabilize, (void *)i);
		}

		//join threads
		for (int i = 0; i<NUMTHREADS; i++){
			pthread_join(gridsim.threads[i], NULL);
		}
	}

	//ascii visualization
	printf("Sandpile after stability has been reached: \n");
	visual_grid(gridsim.sgrid);
	pthread_exit(NULL);

	exit(0);

}