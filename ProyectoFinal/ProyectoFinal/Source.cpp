#include "GL/glut.h"
#include <math.h>
#include <stdarg.h>


void init(void) {
	glMatrixMode(GL_PROJECTION);
	glClearColor(140 / 225.0, 94 / 255.0, 60 / 255.0, 0.0);
	gluOrtho2D(0.0, 225.0, 0.0, 225.0);
}

void pinta(void) {
	glClear(GL_COLOR_BUFFER_BIT);

	glFlush();
}

void main(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowPosition(50, 10);
	glutInitWindowSize(384 * 2, 400 * 2);
	glutCreateWindow("ProyectoFinal");
	glutDisplayFunc(pinta);
	glutMainLoop();
}