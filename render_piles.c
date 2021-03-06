/* 
	 Isabella Jorissen
	 Hw. 5/6
	 Math 389
	 11.11.14
 */

#include "header.h"
grid_simulation_t gridsim;

float * cell_color(int grains){
	static float col[3];
	switch (grains){
		//blue
		case 0:
			col[0] = 1.0;
			col[1] = 1.0;
			col[2] = 1.0;
			break;
		//blue
		case 1:
			col[0] = 0.6;
			col[1] = 0.6;
			col[2] = 0.9;
			break;
		//pink
		case 2:
			col[0] = 0.8;
			col[1] = 0.4;
			col[2] = 0.8;
			break;
		//lavender
		case 3:
			col[0] = 0.6;
			col[1] = 0.4;
			col[2] = 0.9;
			break;
		//purple
		case 4:
			col[0] = 0.6;
			col[1] = 0.2;
			col[2] = 0.7;
			break;
		//more than 4 grains, dark purple
		default:
			col[0] = 0.4;
			col[1] = 0.1;
			col[2] = 0.7;
			break;
	}
	return col;
}

void *loop(void *info){
	int tid = (int)info;
	int iteration = 0;
    while (gridsim.stable != 0) {
 		stabilize(tid);
 		bar_wait(gridsim.barrier);
		if (tid == 0) {
			iteration ++;
			glutPostRedisplay();
			pthread_mutex_lock(&gridsim.stable_lock);
			gridsim.stable = isStable(gridsim.sgrid);
			if(gridsim.stable == 0){
				printf("the grid is stable after %d iterations\n", iteration);
			}
			pthread_mutex_unlock(&gridsim.stable_lock);
 		}
 		bar_wait(gridsim.barrier);
    }
	pthread_exit(NULL);
    return NULL;
}

void display(void){
	int gridH = gridsim.sgrid->height;
	int gridW = gridsim.sgrid->width;
	glClear(GL_COLOR_BUFFER_BIT); //Clear the colour buffer (more buffers later on)  
	glLoadIdentity(); // Load the Identity Matrix to reset our drawing locations
	glTranslatef(-(gridW/2), -(gridH/2), -gridW);
	glShadeModel(GL_FLAT);
	float * color;

	for(float i = 1.0; i<gridH+1; i++){
		glBegin(GL_QUAD_STRIP);
			int fc_cellnum = (i-1)*gridH;
			color = cell_color(gridsim.sgrid->cells[fc_cellnum]);
			// glColor3f(color[0], color[1], color[2]);
			glColor3f(.1, .1, .4);
			glVertex2f(0.0f, i); // The top left corner  
			glVertex2f(0.0f, (i-1)); // The bottom left corner 
			glVertex2f(1.0f, i); //top right
			glVertex2f(1.0f, (i-1));  //bottom right
			//addition verticies
			for(float j = 2.0; j<gridW+1; j++){
				int cellnum = (i-1)*gridH + (j-1);
				if ((j == gridW) || (i==1) || (i==gridH)){
					color[0] = .1;
					color[1] = .1;
					color[2] = .4;
				}
				else{
					color = cell_color(gridsim.sgrid->cells[cellnum]);
				}
				glColor3f(color[0], color[1], color[2]);
				glVertex2f(j, i); 
				glVertex2f(j, (i-1)); 
			}
		glEnd();
	}
	glFlush();      //Finish rendering
}

void reshape (int width, int height) {  
	glViewport(0, 0, (GLsizei)width, (GLsizei)height);
	glMatrixMode(GL_PROJECTION); 
	glLoadIdentity(); 
	gluPerspective(60, (GLfloat)width / (GLfloat)height, 1.0, 100.0); 
	glMatrixMode(GL_MODELVIEW); 
} 

int main (int argc, char **argv){

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE);
	glutInitWindowSize(500,500);
	glutInitWindowPosition (100, 600);
	glutCreateWindow("Sandpiles Simulation");
	glClearColor(0.0,0.0,0.0,0.0);

	barrier_t barr;
	sandgrid_t sandgrid;
	int thread_num = 4;
	int grains = 5000;
	int gridW = 64;
	int gridH = 64;

	grid_simulation_t *gsim =  (grid_simulation_t *)malloc(sizeof(grid_simulation_t));
	gridsim = *gsim;

	printf("Running: %dx%d grid, %d grains until stable, 10 timesteps per round with %d threads.\n", gridW, gridH, grains, thread_num);

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

	glutDisplayFunc(display);
	glutReshapeFunc(reshape);

	glutMainLoop();
	return 0;
}
