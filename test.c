/* 
   Isabella Jorissen
   Hw. 6
   Math 389
   11.16.14
 */
  
#include "header.h"

barrier_t barr;


int main(int argc, char **argv){
	pthread_t pt_data [4];
	bar_init(&barr, 4);

	// printf("Took _____ seconds.\n");

	//initialize threads
	for (int i = 0; i<4; i++){
		pthread_create(&pt_data[i], NULL, stabilize, (void *)i);
	}
	
	for (int i = 0; i<4; i++){
		pthread_join(pt_data[i], NULL);
	}

	exit(0);

}