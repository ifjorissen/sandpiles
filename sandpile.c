/* 
   Isabella Jorissen
   Hw. 6
   Math 389
   11.16.14
 */
   
#include "sandgrid.h"
#include <stdio.h>
#include <time.h>
#include <pthread.h> 
#include <stdlib.h>
#include <unistd.h>

// typedef struct pthread_data_t{

// }pthread_data_t;


int main(int argc, char **argv){
	pthread_data_t pt_data [4];

	printf("Running: 51x51 grid, 5,0000 grains, 2,500 rounds with one thread.\n");
	sandgrid_t *sgrid = init_sandgrid(51, 51);
	pthread_create(&sgrid->threads, NULL, stabilize, sgrid);
	printf("Took _____ seconds.\n");

	printf("Running: 51x51 grid, 5,0000 grains, 2,500 rounds with one thread.\n");
	sandgrid_t *sgrid = init_sandgrid(51, 51);

	//initialize threads
	for (int i = 0; i<4; i++){
		pthread_create(&sgrid->threads[i], NULL, stabilize, sgrid);
	}

	// //divide grid into regions
	// pthread_create(&sgrid->tid[0], NULL, stabilize, pt_data[0]);
	// pthread_create(&sgrid->tid[1], NULL, stabilize, pt_data[1]);
	// pthread_create(&sgrid->tid[2], NULL, stabilize, pt_data[2]);
	// pthread_create(&sgrid->tid[3], NULL, stabilize, pt_data[3]);
	printf("Took _____ seconds.\n");
}