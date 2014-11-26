/* 
   Isabella Jorissen
   Hw. 6
   Math 389
   11.16.14
 */

#include "header.h"
grid_simulation_t gridsim;
barrier_t barr;
sandgrid_t sandy;


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

// void *stabilize(void *arg){
// 	printf("stabilize called\n");
// 	sandgrid_t *sgrid = arg;
// 	//100 loops
// 	for (int k = 0; k<1000; k++){
// 		for (int i = 0; i<sgrid->height; i++){
// 			for(int j= 0; j<sgrid->width; j++){
// 				int cellnum = i*(sgrid->width)+j;
// 				if(sgrid->cells[cellnum]>=4){
// 					// fire_cell(sgrid, cellnum)
// 					int cellN = (i-1)*(sgrid->width)+j;
// 					int cellS = (i+1)*(sgrid->width)+j;
// 					int cellE = i*(sgrid->width)+(j+1);
// 					int cellW = i*(sgrid->width)+(j-1);
// 					sgrid->cells[cellnum] -= 4;
// 					sgrid->cells[cellN] += 1;
// 					sgrid->cells[cellS] += 1;
// 					sgrid->cells[cellE] += 1;
// 					sgrid->cells[cellW] += 1;
// 				}
// 			}
// 		}
// 	}
// 	// visual_grid(sgrid);
// 	return NULL;
// }

void *stabilize(void *info){
	int tNum = (int)info;
	// pthread_data *pt_info = info;
	printf("stabilize called from thread: %d\n", tNum);
	bar_wait(&barr);
	// visual_grid(sgrid);
	return NULL;
}

void init_cells(sandgrid_t *sgrid){
	for (int i =0; i<sgrid->height; i++){
		for(int j=0; j<sgrid->width; j++){
			int cellnum = i*(sgrid->width)+j;
			if ((i == sgrid->height/2) && (j == sgrid->width/2)){
				sgrid->cells[cellnum]= 1000;
			}
			else{
				sgrid->cells[cellnum] = 0;
			}
		}
	}
}

void init_sandgrid(sandgrid_t *sgrid, int w, int h){
	// sandgrid_t *sgrid = (sandgrid_t *)malloc(sizeof(sandgrid_t));
	sgrid->cells = (int *)malloc(sizeof(int)*(w)*(h));
	sgrid->width = w;
	sgrid->height = h;
	// sgrid->cell_cap= CAPACITY;
	init_cells(sgrid);

	// return sgrid;
}

// int isFull(sandgrid_t *sandgrid, int cell){

// }
