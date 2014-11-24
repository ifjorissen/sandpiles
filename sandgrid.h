/* 
   Isabella Jorissen
   Hw. 6
   Math 389
   11.16.14
 */

#ifndef __SANDGRID_H
#define __SANDGRID_H

#include <pthread.h> 


typedef struct sandgrid_t{
	// int cell_cap; //cell capacity (set to 4 by default)
	pthread_t threads;      // thread info
	int width;
	int height;
	int * cells; //pointer to a 1-d representation of the 2D grid
				  //array of cells which will hold the number of grains
} sandgrid_t;

sandgrid_t *init_sandgrid(int width, int height);
void visual_grid(sandgrid_t *sandgrid);
int isFull(sandgrid_t *sandgrid, int cell);
void *stabilize(void *arg);

#endif