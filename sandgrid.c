/* 
   Isabella Jorissen
   Hw. 6
   Math 389
   11.16.14
 */

#include "header.h"
grid_simulation_t gridsim;

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


int isStable(sandgrid_t *sgrid){
	//check all the cells, skipping the 
	//first and last columns
	// & first and last rows
	int count = 0;
	for(int j = 1; j<sgrid->height; j++){
		for (int k = 1; k<sgrid->width; k++){
			int cellnum = j*(sgrid->width)+k;
			if(sgrid->cells[cellnum]>=4){
				count++;
			}
		}
	}
	return count;
}

void stabilize(int tid){
	int gridW = gridsim.sgrid->width;
	int gridH = gridsim.sgrid->height;
	int regionLO = (gridH)/NUMTHREADS * tid;
	int regionHI = (gridH)/NUMTHREADS * (tid+1) - 1;
	// printf("stabilize called from thread: %d. region lower bound: %d, region upper bound: %d\n", tid, regionLO, regionHI);
	
	//10 iterations
	for(int i = 0; i<10; i++){
		for(int j = regionLO; j<=regionHI; j++){
			for (int k = 0; k < gridW; k++){
				//we're looking at a boundary sink cell, so we don't check the max or fire
				if(!((j == 0) || (j == gridH) || (k == 0) || (k==gridW))){
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
	}
	// printf("end of stabilize from thread: %d\n", tid);
}

void displayGRID(){
	// bar_wait(gridsim.barrier);
	visual_grid(gridsim.sgrid);
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

