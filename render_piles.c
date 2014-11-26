/* 
	 Isabella Jorissen
	 Hw. 5/6
	 Math 389
	 11.11.14
 */

#include "header.h"

#define gridW (25)
#define gridH (25)

sandgrid_t *sgrid;

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

void display(void){
	glClear(GL_COLOR_BUFFER_BIT); //Clear the colour buffer (more buffers later on)  
	glLoadIdentity(); // Load the Identity Matrix to reset our drawing locations
	glTranslatef(-(gridW/2), -(gridH/2), -gridW);
	glShadeModel(GL_FLAT);
	float * color;

	for(float i = 1.0; i<gridH+1; i++){
		glBegin(GL_QUAD_STRIP);
			int fc_cellnum = (i-1)*gridH;
			color = cell_color(sgrid->cells[fc_cellnum]);
			glColor3f(color[0], color[1], color[2]);
			glVertex2f(0.0f, i); // The top left corner  
			glVertex2f(0.0f, (i-1)); // The bottom left corner 
			glVertex2f(1.0f, i); //top right
			glVertex2f(1.0f, (i-1));  //bottom right
			//addition verticies
			for(float j = 2.0; j<gridW+1; j++){
				int cellnum = (i-1)*gridH + (j-1);
				printf("cell num: %d. grains: %d\n", cellnum, sgrid->cells[cellnum]);
				color = cell_color(sgrid->cells[cellnum]);
				glColor3f(color[0], color[1], color[2]);
				glVertex2f(j, i); 
				glVertex2f(j, (i-1)); 
			}
		glEnd();
	}
	glFlush();      //Finish rendering
}

void reshape (int width, int height) {  
	glViewport(0, 0, (GLsizei)width, (GLsizei)height); /
	glMatrixMode(GL_PROJECTION); 
	glLoadIdentity(); 
	gluPerspective(60, (GLfloat)width / (GLfloat)height, 1.0, 100.0); 
	glMatrixMode(GL_MODELVIEW); 
} 

int main (int argc, char **argv)
{
	sgrid = init_sandgrid(gridW, gridH);
	pthread_create(&sgrid->threads, NULL, stabilize, sgrid);

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE);
	glutInitWindowSize(500,500);
	glutInitWindowPosition (100, 500);

	glutCreateWindow("Intro");
	glClearColor(0.0,0.0,0.0,0.0);

	glutDisplayFunc(display);
	glutReshapeFunc(reshape);

	glutMainLoop();
	return 0;
}