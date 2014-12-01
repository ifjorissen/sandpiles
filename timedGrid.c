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
	int threading [5] =  {1, 2, 4, 8, 16};
	int grain_vals [5] = {100, 500, 1000, 2500, 5000};
	double cpu_time_used [30]; //threading*grain_vals
	int gridW = 64;
	int gridH = 64;

	//run the program with the 6 different grain values and the 5 differnt thread values
	for (int i = 0; i<5; i++){
		for (int j=0; j<5; j++){
			clock_t start = clock();
			barrier_t barr;
			sandgrid_t sandgrid;
			int thread_num = threading[j];
			int grains = grain_vals[i];

			// char *test = "is this working?";
			grid_simulation_t *gsim =  (grid_simulation_t *)malloc(sizeof(grid_simulation_t));
			gridsim = *gsim;

			printf("\nRunning until stable: %dx%d grid, %d grains, 10 timesteps per round with %d threads.\n", gridW, gridH, grains, thread_num);

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
				pthread_create(&gridsim.threads[i], NULL, loop, (void *)i);
			}

			for (int i = 0; i<thread_num; i++){
				pthread_join(gridsim.threads[i], NULL);
			}

			clock_t end = clock();
		    cpu_time_used[i*5 + j] = ((double) (end - start)) / CLOCKS_PER_SEC;
		    printf("the grid took %f seconds to stabilize\n", cpu_time_used[i*5 + j]);
		}
	}
	printf("\nRESULTS:\n");
	for(int i = 0; i<5; i++){
		for (int j = 0; j<5; j++){
			printf("Stabilizing a %dx%d grid with %d grains and %d threads took: %f seconds\n", gridW, gridH, grain_vals[i], threading[j], cpu_time_used[i*5 + j]);
		}
		printf("\n");
	}
	pthread_exit(NULL);
	exit(0);

}