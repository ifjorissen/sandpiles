/* 
   Isabella Jorissen
   Hw. 6
   Math 389
   11.16.14
 */

#include "header.h"
grid_simulation_t gridsim;
// barrier_t barr;
// sandgrid_t sandy;


// int fire_cell(sandgrid_t *sgrid, int cellnum){
// 	sgrid->cells[cellnum] -= 4;
// 	int cellN = i-1*(sgrid->width)+j;
// 	//north
// 	//south
// 	//east
// 	//west

// }

void visual_grid(sandgrid_t *sgrid){
	for(int i = 0; i < sgrid->height; i++){
		printf("\n");
		for (int j = 0; j < sgrid->width; j++){
			int cellnum = i*(sgrid->width)+j;
			printf("| %d ", sgrid->cells[cellnum]);
		}
	}
	printf("\n");
}


//TO DO: add mutex_try_lock() with a condition code so that threads wait

void *stabilize(void *info){
	int tid = (int)info;
	int gridW = gridsim.sgrid->width;
	int gridH = gridsim.sgrid->height;
	int regionLO = (gridH)/NUMTHREADS * tid;
	int regionHI = (gridH)/NUMTHREADS * (tid+1) - 1;
	// gridsim.boundaries[tid] = regionHI;
	printf("stabilize called from thread: %d. region lower bound: %d, region upper bound: %d\n", tid, regionLO, regionHI);
	
	//100 iterations
	for(int i = 0; i<100; i++){
		for(int j = 0; j<=regionHI; j++){
			for (int k = 0; k < gridW; k++){
				int cellnum = j*(gridW)+k;
				int cellN = (j-1)*(gridW)+k;
				int cellE = j*(gridW)+(k+1);
				int cellW = j*(gridW)+(k-1);
				int cellS = (j+1)*(gridW)+k;
				//we need to lock the higher row and this row (thus, higher mutex)
				if ((j==regionHI)&&(tid!=(NUMTHREADS-1))){
					//lock the important bits
					pthread_mutex_lock(&gridsim.mutex[tid]);
					// printf("locked mutex num: %d in critical section row: %d, tid: %d\n", tid, j, tid);
					if(gridsim.sgrid->cells[cellnum] >= 4){
						gridsim.sgrid->cells[cellnum] -= 4;
						gridsim.sgrid->cells[cellS] += 1;
						gridsim.sgrid->cells[cellN] += 1;
						gridsim.sgrid->cells[cellE] += 1;
						gridsim.sgrid->cells[cellW] += 1;
					}
					pthread_mutex_unlock(&gridsim.mutex[tid]);
					// printf("unlocked mutex num: %d in critical section row: %d, tid: %d\n", tid, j, tid);
				}
				//we need to lock the lower row (thus, lower mutex) and this row
				else if ((j==regionLO)&&(tid!= 0)){
					pthread_mutex_lock(&gridsim.mutex[tid-1]);
					// printf("locked mutex num: %d in critical section row: %d, tid: %d\n", tid-1, j, tid);
					if(gridsim.sgrid->cells[cellnum] >= 4){
						gridsim.sgrid->cells[cellnum] -= 4;
						gridsim.sgrid->cells[cellS] += 1;
						gridsim.sgrid->cells[cellN] += 1;
						gridsim.sgrid->cells[cellE] += 1;
						gridsim.sgrid->cells[cellW] += 1;
					}
					pthread_mutex_unlock(&gridsim.mutex[tid-1]);
					// printf("unlocked mutex num: %d in critical section row: %d, tid: %d\n", tid-1, j, tid);
				}
				//we don't need a lock
				else{
					if(gridsim.sgrid->cells[cellnum] >= 4){
						gridsim.sgrid->cells[cellnum] -= 4;
						gridsim.sgrid->cells[cellS] += 1;
						gridsim.sgrid->cells[cellN] += 1;
						gridsim.sgrid->cells[cellE] += 1;
						gridsim.sgrid->cells[cellW] += 1;
					}
				}
			}

		}
	}

	bar_wait(gridsim.barrier);
	return NULL;
}

void init_cells(sandgrid_t *sgrid){
	for (int i =0; i<sgrid->height; i++){
		for(int j=0; j<sgrid->width; j++){
			int cellnum = i*(sgrid->width)+j;
			if ((i == sgrid->height/2 - 1) && (j == sgrid->width/2 - 1)){
				sgrid->cells[cellnum]= NUMGRAINS;
			}
			else{
				sgrid->cells[cellnum] = 0;
			}
		}
	}
}

void init_sandgrid(sandgrid_t *sgrid, int w, int h){
	sgrid->cells = (int *)malloc(sizeof(int)*(w)*(h));
	sgrid->width = w;
	sgrid->height = h;
	init_cells(sgrid);
}

