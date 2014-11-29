/* 
   Isabella Jorissen
   Hw. 6
   Math 389
   11.16.14
   header.h: a header file for sandpiles
 */

#ifndef __HEADER_H
#define __HEADER_H


#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#include <OpenGL/glext.h>
#include <GLUT/glut.h>
#include <stdio.h>
#include <time.h>
#include <pthread.h> 
#include <stdlib.h>

#define NUMTHREADS (4)
#define NUMGRAINS (100)

typedef struct _barrier_t{
	int count;
	pthread_cond_t last_thread;
	pthread_mutex_t mutex;
}barrier_t;

void *bar_init(barrier_t *barrier, int pt_num);
void *bar_wait(barrier_t *barrier); 

typedef struct sandgrid_t{
	// int cell_cap; //cell capacity (set to 4 by default)
	int width;
	int height;
	int * cells; //pointer to a 1-d representation of the 2D grid
				  //array of cells which will hold the number of grains
} sandgrid_t;

void init_sandgrid(sandgrid_t *sandgrid, int width, int height);
void visual_grid(sandgrid_t *sandgrid);
void stabilize(int info);
void displayGRID();
int isStable(sandgrid_t *sandgrid);

typedef struct grid_simulation_t{
	int stable;
	pthread_mutex_t stable_lock;
	sandgrid_t *sgrid;
	pthread_t threads [NUMTHREADS];
	pthread_mutex_t mutex [NUMTHREADS-1];
	pthread_cond_t cond [NUMTHREADS-1];
	barrier_t *barrier;
}grid_simulation_t;


#endif