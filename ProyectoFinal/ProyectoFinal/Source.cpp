#include <stdlib.h>
#include "GL/glut.h"
#include <math.h>
#include <stdarg.h>

static int width;
static int height;
static void visorUsuario();
static void visorAutomatico();
static void visorInstrucciones();

static void pinta(void) {

const int PALETA = 3;

void init(void) {
  width = 500;
  height = 500;
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

	//Visor controlado por el usuario
	glViewport(0, 0, (2*width)/ 3, height / 2);
	visorUsuario();

	//Visor automatico
	glViewport(0, height/2, (2 * width) / 3, height / 2);
	visorAutomatico();

	//Visor de instrucciones
	glViewport((2 * width) / 3, 0, width / 3, height);
	visorInstrucciones();	

	glFlush();
}

static void visorInstrucciones()
{
	glLoadIdentity();
	glColor3f(0, 1, 0.0f);
	gluLookAt(0.0, 0.0, 0, 0, 0, -1.0, 0.0, 1.0, 0.0);

	glBegin(GL_QUADS);
	glVertex3d(-1, -1, 0);
	glVertex3d(-1, 1, 0);
	glVertex3d(1, 1, 0);
	glVertex3d(1, -1, 0);
	glEnd();
}

static void visorUsuario()
{
	glClear(GL_COLOR_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
  gluLookAt(0.0, 0.0, 0, 0, 0, -1.0, 0.0, 1.0, 0.0);

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

}

static void visorAutomatico()
{
	glClear(GL_COLOR_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
  gluLookAt(0.0, 0.0, 0, 0, 0, -1.0, 0.0, 1.0, 0.0);

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

}

static void reshape(int w, int h) {
	width = w;
	height = h;
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glFrustum(-2.0, 2.0, -2.0, 2.0, 0, 5.0);
	glMatrixMode(GL_MODELVIEW);
}

int main(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(width, height);
	glutCreateWindow("Proyecto Final");
	init();
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glShadeModel(GL_FLAT);
	glutDisplayFunc(pinta);
	glutReshapeFunc(reshape);
	glutMainLoop();
	return 0;
}