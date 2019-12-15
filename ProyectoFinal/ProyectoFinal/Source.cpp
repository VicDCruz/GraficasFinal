#include <stdlib.h>
#include <GL/glut.h>
#include <math.h>

const int PALETA = 3;
int WINWIDTH = 1000, WINHEIGHT = 500; // Initial display-window size.
const float LENGTH = 1000;
const float XWMIN = -LENGTH / 2, XWMAX = LENGTH, YWMIN = -LENGTH / 2, YWMAX = LENGTH, PNEAR = 0, PFAR = LENGTH / 0.7;

// TIPO DE MATERIALES
const float NO_MAT[] = { 0, 0, 0, 1 };
const float MAT_AMBIENT[] = { 0.7, 0.7, 0.7, 1/2 };
// const float MAT_AMBIENT_COLOR[] = { 0.8, 0.8, 0.2, 1 };
const float MAT_AMBIENT_COLOR[] = { 1, 1, 1, 1/2 };
// const float MAT_DIFFUSE[] = { 0.1, 0.5, 0.8, 1 };
const float MAT_DIFFUSE[] = { 1, 1, 1, 1 };
const float MAT_SPECULAR[] = { 1, 1, 1, 1 };
const float NO_SHININESS = 0;
const float LOW_SHININESS = 5;
const float HIGH_SHININESS = 100;
const float MAT_EMISSION[] = { 0.3, 0.2, 0.2, 0 };

// PROPIEDADES DE LUCES
const float AMBIENT[] = { 0, 0, 0, 1 };
const float DIFFUSE[] = { 1, 1, 1, 1 };
const float SPECULAR[] = { 1, 1, 1, 1 };
// const float POSITION[] = { 1, 1, 0.3, 0 };
const float POSITION[] = { 500, 500, 500, 0 };

// INIT LUCES
float model_AMBIENT[] = { 0.4, 0.4, 0.4, 1 };
int model_two_side = 1;
int viewpoint = 0;

void init(void) {
	glClearColor(1, 1, 1, 0);

	glMatrixMode(GL_PROJECTION);
	glOrtho(XWMIN, XWMAX, YWMIN, YWMAX, PNEAR, PFAR);
	glMatrixMode(GL_MODELVIEW);
	glClear(GL_COLOR_BUFFER_BIT);

	glLightfv(GL_LIGHT0, GL_AMBIENT, AMBIENT);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, DIFFUSE);
	glLightfv(GL_LIGHT0, GL_SPECULAR, SPECULAR);
	glLightfv(GL_LIGHT0, GL_POSITION, POSITION);
}

void ponReflex(int type)
{
	/*
		1 - Difusa
		2 - Difusa y Especular, Bajo Brillo
		3 - Difusa y Especular, Alto Brillo
		4 - Difusa y Emisión
		5 - Ambiente y Disufa
		6 - Ambiente, Difusa y Especular, Bajo Brillo
		7 - Ambiente, Difusa y Especular, Alto Brillo
		8 - Ambiente, Difusa y Emisión
		9 - Color Ambiente y Difusa
		10 - Color Ambiente, Difusa y Especular, Bajo Brillo
		11 - Color Ambiente, Difusa y Especular, Alto Brillo
		12 - Color Ambiente, Difusa y Emisión
	*/
	switch (type)
	{
	case 1:
		glMaterialfv(GL_FRONT, GL_AMBIENT, NO_MAT);
		glMaterialfv(GL_FRONT, GL_DIFFUSE, MAT_DIFFUSE);
		glMaterialfv(GL_FRONT, GL_SPECULAR, NO_MAT);
		glMaterialf(GL_FRONT, GL_SHININESS, NO_SHININESS);
		glMaterialfv(GL_FRONT, GL_EMISSION, NO_MAT);
		break;
	case 2:
		glMaterialfv(GL_FRONT, GL_AMBIENT, NO_MAT);
		glMaterialfv(GL_FRONT, GL_DIFFUSE, MAT_DIFFUSE);
		glMaterialfv(GL_FRONT, GL_SPECULAR, MAT_SPECULAR);
		glMaterialf(GL_FRONT, GL_SHININESS, LOW_SHININESS);
		glMaterialfv(GL_FRONT, GL_EMISSION, NO_MAT);
		break;
	case 3:
		glMaterialfv(GL_FRONT, GL_AMBIENT, NO_MAT);
		glMaterialfv(GL_FRONT, GL_DIFFUSE, MAT_DIFFUSE);
		glMaterialfv(GL_FRONT, GL_SPECULAR, MAT_SPECULAR);
		glMaterialf(GL_FRONT, GL_SHININESS, HIGH_SHININESS);
		glMaterialfv(GL_FRONT, GL_EMISSION, NO_MAT);
		break;
	case 4:
		glMaterialfv(GL_FRONT, GL_AMBIENT, NO_MAT);
		glMaterialfv(GL_FRONT, GL_DIFFUSE, MAT_DIFFUSE);
		glMaterialfv(GL_FRONT, GL_SPECULAR, NO_MAT);
		glMaterialf(GL_FRONT, GL_SHININESS, NO_SHININESS);
		glMaterialfv(GL_FRONT, GL_EMISSION, MAT_EMISSION);
		break;
	case 5:
		glMaterialfv(GL_FRONT, GL_AMBIENT, MAT_AMBIENT);
		glMaterialfv(GL_FRONT, GL_DIFFUSE, MAT_DIFFUSE);
		glMaterialfv(GL_FRONT, GL_SPECULAR, NO_MAT);
		glMaterialf(GL_FRONT, GL_SHININESS, NO_SHININESS);
		glMaterialfv(GL_FRONT, GL_EMISSION, NO_MAT);
		break;
	case 6:
		glMaterialfv(GL_FRONT, GL_AMBIENT, MAT_AMBIENT);
		glMaterialfv(GL_FRONT, GL_DIFFUSE, MAT_DIFFUSE);
		glMaterialfv(GL_FRONT, GL_SPECULAR, MAT_SPECULAR);
		glMaterialf(GL_FRONT, GL_SHININESS, LOW_SHININESS);
		glMaterialfv(GL_FRONT, GL_EMISSION, NO_MAT);
		break;
	case 7:
		glMaterialfv(GL_FRONT, GL_AMBIENT, MAT_AMBIENT);
		glMaterialfv(GL_FRONT, GL_DIFFUSE, MAT_DIFFUSE);
		glMaterialfv(GL_FRONT, GL_SPECULAR, MAT_SPECULAR);
		glMaterialf(GL_FRONT, GL_SHININESS, HIGH_SHININESS);
		glMaterialfv(GL_FRONT, GL_EMISSION, NO_MAT);
		break;
	case 8:
		glMaterialfv(GL_FRONT, GL_AMBIENT, MAT_AMBIENT);
		glMaterialfv(GL_FRONT, GL_DIFFUSE, MAT_DIFFUSE);
		glMaterialfv(GL_FRONT, GL_SPECULAR, NO_MAT);
		glMaterialf(GL_FRONT, GL_SHININESS, NO_SHININESS);
		glMaterialfv(GL_FRONT, GL_EMISSION, MAT_EMISSION);
		break;
	case 9:
		glMaterialfv(GL_FRONT, GL_AMBIENT, MAT_AMBIENT_COLOR);
		glMaterialfv(GL_FRONT, GL_DIFFUSE, MAT_DIFFUSE);
		glMaterialfv(GL_FRONT, GL_SPECULAR, NO_MAT);
		glMaterialf(GL_FRONT, GL_SHININESS, NO_SHININESS);
		glMaterialfv(GL_FRONT, GL_EMISSION, NO_MAT);
		break;
	case 10:
		glMaterialfv(GL_FRONT, GL_AMBIENT, MAT_AMBIENT_COLOR);
		glMaterialfv(GL_FRONT, GL_DIFFUSE, MAT_DIFFUSE);
		glMaterialfv(GL_FRONT, GL_SPECULAR, MAT_SPECULAR);
		glMaterialf(GL_FRONT, GL_SHININESS, LOW_SHININESS);
		glMaterialfv(GL_FRONT, GL_EMISSION, NO_MAT);
		break;
	case 11:
		glMaterialfv(GL_FRONT, GL_AMBIENT, MAT_AMBIENT_COLOR);
		glMaterialfv(GL_FRONT, GL_DIFFUSE, MAT_DIFFUSE);
		glMaterialfv(GL_FRONT, GL_SPECULAR, MAT_SPECULAR);
		glMaterialf(GL_FRONT, GL_SHININESS, HIGH_SHININESS);
		glMaterialfv(GL_FRONT, GL_EMISSION, NO_MAT);
		break;
	case 12:
		glMaterialfv(GL_FRONT, GL_AMBIENT, MAT_AMBIENT_COLOR);
		glMaterialfv(GL_FRONT, GL_DIFFUSE, MAT_DIFFUSE);
		glMaterialfv(GL_FRONT, GL_SPECULAR, NO_MAT);
		glMaterialf(GL_FRONT, GL_SHININESS, NO_SHININESS);
		glMaterialfv(GL_FRONT, GL_EMISSION, MAT_EMISSION);
		break;
	default:
		break;
	}
}

void dibujaCubo(float largo, float x, float y, float z) {
	glPushMatrix();
		glTranslatef(x, y, z);
		glutSolidCube(largo);
	glPopMatrix();
}

void dibujaParedes(float alpha)
{
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	ponReflex(5);
	// dibujaCubo(1000, 250, 250, -100);
	// glPolygonMode (GL_FRONT_AND_BACK, GL_LINE); // Wire-frame back face.
	// glColor4f(0.9, 0.5, 0.9, 1);

	int lado = 750;
	//Bottom Face of the cube - vertex definition
	glBegin(GL_POLYGON);
		glColor4f(0.2, 0.2, 0.8, alpha);
		glVertex3f(-lado, 0, -lado);
		glVertex3f(lado, 0, -lado);
		glVertex3f(lado, 0, lado);
		glVertex3f(-lado, 0, lado);
	glEnd();

	//Front Face of the cube - vertex definition
	glBegin(GL_POLYGON);
		glColor4f(0.0, 1.0, 0.0, alpha);
		glVertex3f(-lado, 0, -lado);
		glVertex3f(-lado, lado, -lado);
		glVertex3f(lado, lado, -lado);
		glVertex3f(lado, 0, -lado);
	glEnd();

	//Back Face of the cube - vertex definition
	glBegin(GL_POLYGON);
		glColor4f(1.0, 0.0, 0.0, alpha);
		glVertex3f(lado, 0, -lado);
		glVertex3f(lado, lado, -lado);
		glVertex3f(lado, lado, lado);
		glVertex3f(lado, 0, lado);
	glEnd();

	//Right Face of the cube - vertex definition
	glBegin(GL_POLYGON);
		glColor4f(1.0, 0.0, 1.0, alpha);
		glVertex3f(lado, 0, lado);
		glVertex3f(lado, lado, lado);
		glVertex3f(-lado, lado, lado);
		glVertex3f(-lado, 0, lado);
	glEnd();

	//Left Face of the cube - vertex definition
	glBegin(GL_POLYGON);
		glColor4f(0.7, 0.7, 0.0, alpha);
		glVertex3f(-lado, 0, lado);
		glVertex3f(-lado, lado, lado);
		glVertex3f(-lado, lado, -lado);
		glVertex3f(-lado, 0, -lado);
	glEnd();

	//Upper Face of the cube - vertex definition
	glBegin(GL_POLYGON);
		glColor4f(0.7, 0.7, 0.3, alpha);
		glVertex3f(-lado, lado, -lado);
		glVertex3f(lado, lado, -lado);
		glVertex3f(lado, lado, lado);
		glVertex3f(-lado, lado, lado);
	glEnd();

	glDisable(GL_BLEND);
}

void dibujaEsfera(float radio, float x, float y, float z) {
	int nLong = 10, nLat = 12;
	glPushMatrix();
		glTranslatef(x, y, z);
		ponReflex(6);
		glutSolidSphere(radio, nLong, nLat);
	glPopMatrix();
}

void dibujaPiramide(float radioBase, float altura, float x, float y, float z) {
	int nLong = 8, nLat = 6;
	glPushMatrix();
		glTranslatef(x, y, z);
		ponReflex(7);
		glutSolidCone(radioBase, altura, nLong, nLat);
	glPopMatrix();
}

void dibujaPiso(float largo, int n, float colores[][PALETA], int rows) {
	int lados = 4, a, b;
	int randMaterial = floor(rand() % 12) + 1;
	ponReflex(randMaterial);
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
	glColor3f(0.0, 0.0, 1.0);

	int same = 400;
	gluLookAt(same, same, same, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
	// gluLookAt(0, 0, same, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
	// gluLookAt(-1, 1, 1, 0, 0, 0, 0, 1.0, 0.0);

	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, model_AMBIENT);
	glLightModeli(GL_LIGHT_MODEL_LOCAL_VIEWER, viewpoint);
	glLightModeli(GL_LIGHT_MODEL_TWO_SIDE, 1);

	glEnable(GL_LIGHT0);
	glEnable(GL_LIGHTING);

	glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);
	glEnable(GL_COLOR_MATERIAL);

	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

	glPushMatrix();
	glTranslatef(0, 0, 0);
		glColor3f(1, 1, 0);
		dibujaEsfera(30, -5, -5, 0);

		glColor3f(1, 0, 1);
		dibujaEsfera(30, 450, -5, 0);

		glColor3f(0, 0, 0);
		dibujaPiramide(40, 60, -5, 450, 0);

		glColor3f(0, 1, 1);
		dibujaPiramide(40, 60, 450, 450, 0);
	glPopMatrix();

	int largo = 15, pisos = 15, h = 0;
	float cte = largo / pisos;
	int n = pisos * 2;
	for (int i = 0; i < pisos; i++) {
		float colores[][PALETA] = {
			{1, 1, 0.2},
			{1, 0.7, 0.1},
			{1, 0.4, 0.3},
			{1, 0.1, 0.1},
			{0.9, 0.5, 0.2},
			{0.8, 0.9, 0.4},
			{0.7, 0.7, 0.4},
			{0.7, 0, 0.1},
			{0.3, 0.1, 0.7},
		};
		int rows = sizeof colores / sizeof colores[0];
		glPushMatrix();
		glTranslatef(0.0, 0.0, h);
		dibujaPiso(largo, n, colores, rows);
		glPopMatrix();
		h = largo;
		largo -= cte;
		n -= 2;
	}

	glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT);
	dibujaParedes(0.5);

	glFlush();
}

void reshapeFcn(GLint newWidth, GLint newHeight)
{
	glViewport(0, 0, newWidth, newHeight);
    glMatrixMode(GL_PROJECTION);
	// glOrtho(XWMIN, XWMAX, YWMIN, YWMAX, PNEAR, PFAR);
	glFrustum(XWMIN, XWMAX, YWMIN, YWMAX, PNEAR, PFAR);
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
	glutReshapeFunc(reshapeFcn);
	glutMainLoop();
	return 1;
}