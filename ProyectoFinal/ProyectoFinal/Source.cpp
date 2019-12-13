#include <stdlib.h>
#include "GL/glut.h"
#include <math.h>
#include <stdarg.h>

const int PALETA = 3;
const int WINWIDTH = 500, WINHEIGHT = 500; // Initial display-window size.

void init(void) {
	glClearColor(1.0, 1.0, 1.0, 0.0);
}

void dibujaCubo(float largo, float x, float y, float z) {
	glPushMatrix();
	glTranslatef(x, y, z);
	glutSolidCube(largo);
	glPopMatrix();
}

void dibujaEsfera(float radio, float x, float y, float z) {
	int nLong = 10, nLat = 12;
	glPushMatrix();
	glTranslatef(x, y, z);
	glutSolidSphere(radio, nLong, nLat);
	glPopMatrix();
}

void dibujaPiramide(float radioBase, float altura, float x, float y, float z) {
	int nLong = 8, nLat = 6;
	glPushMatrix();
	glTranslatef(x, y, z);
	glutSolidCone(radioBase, altura, nLong, nLat);
	glPopMatrix();
}

void dibujaPiso(float largo, int n, float colores[][PALETA], int rows) {
	int lados = 4, a, b;
	for (int i = 0; i < lados; i++)
	{
		a = i == 1 ? n - 1 : 0;
		b = i == 2 ? n - 1 : 0;
		for (int j = 0; j < n; j++)
		{
			int r = floor(rand() % rows);
			glColor3f(colores[r][0], colores[r][1], colores[r][2]);
			dibujaCubo(largo, largo * a, largo * b, 0);
			a = (i == 0 || i == 2) ? a + 1 : a;
			b = (i == 1 || i == 3) ? b + 1 : b;
		}
	}
}


void pinta(void) {
	glClear(GL_COLOR_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(2.0, 2.0, 2.0, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0);

	int largo = 10, pisos = 20, h = 0;
	for (int i = 0; i < pisos; i++) {
		float colores[][PALETA] = {
			{0, 1, 0},
			{1, 0, 1}
		};
		int rows = sizeof colores / sizeof colores[0];
		glPushMatrix();
		glTranslatef(0.0, 0.0, h);
		dibujaPiso(largo, 5, colores, rows);
		glPopMatrix();
		h += largo;
		largo--;
		pisos -= 2;
	}

	glPushMatrix();
	glTranslatef(0, 0, 0);

	glColor3f(1.0, 1.0, 0.0);
	dibujaEsfera(10, -5, -5, 0);

	glColor3f(1.0, 1.0, 0.0);
	dibujaEsfera(10, 45, -5, 0);

	glColor3f(0.0, 0.0, 0.0);
	dibujaPiramide(10, 20, -5, 45, 0);

	glColor3f(0.0, 0.0, 0.0);
	dibujaPiramide(10, 20, 45, 45, 0);

	glPopMatrix();

	glFlush();
}

void winReshapeFcn(GLint newWidth, GLint newHeight)
{
	glViewport(0, 0, newWidth, newHeight);
	glMatrixMode(GL_PROJECTION);
	glOrtho(-2.0, 2.0, -2.0, 2.0, 0.0, 5.0);
	glMatrixMode(GL_MODELVIEW);
	glClear(GL_COLOR_BUFFER_BIT);
}

int main(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(WINWIDTH, WINHEIGHT);
	glutCreateWindow("Proyecto Final");
	init();
	glutDisplayFunc(pinta);
	glutReshapeFunc(winReshapeFcn);
	glutMainLoop();
}