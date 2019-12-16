#include <stdlib.h>
#include <GL/glut.h>
#include <math.h>
#include <stdio.h>

const int PALETA = 3;
int WINWIDTH = 1000, WINHEIGHT = 500; // Initial display-window size.
int tecla;
unsigned char teclas[256];
double camUser[6];
double auxCamUser[6];
int paramCam;
int paramFoc;
bool poniendoFoc;
bool moviendoCam;
const float LENGTH = 600;
const float XWMIN = -LENGTH / 2, XWMAX = LENGTH, YWMIN = -LENGTH / 2, YWMAX = LENGTH, PNEAR = 0, PFAR = LENGTH / 0.7;
double x;
// TIPO DE MATERIALES
const float NO_MAT[] = { 0, 0, 0, 1 };
const float MAT_AMBIENT[] = { 0.7, 0.7, 0.7, 1 / 2 };
// const float MAT_AMBIENT_COLOR[] = { 0.8, 0.8, 0.2, 1 };
const float MAT_AMBIENT_COLOR[] = { 1, 1, 1, 1 / 2 };
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
const float POSITION1[] = { -500, 500, 500, 0 };
float userColor[4];
float userPos[4];

float model_AMBIENT[] = { 0.4, 0.4, 0.4, 1 };
int model_two_side = 1;
int viewpoint = 0;

void init(void) {
	glClearColor(0, 0.1, 0, 0);

	glMatrixMode(GL_PROJECTION);
	glOrtho(XWMIN, XWMAX, YWMIN, YWMAX, PNEAR, PFAR);
	glMatrixMode(GL_MODELVIEW);
	glClear(GL_COLOR_BUFFER_BIT);

	glLightfv(GL_LIGHT0, GL_AMBIENT, AMBIENT);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, DIFFUSE);
	glLightfv(GL_LIGHT0, GL_SPECULAR, SPECULAR);
	glLightfv(GL_LIGHT0, GL_POSITION, POSITION);


	glLightfv(GL_LIGHT1, GL_AMBIENT, AMBIENT);
	glLightfv(GL_LIGHT1, GL_DIFFUSE, DIFFUSE);
	glLightfv(GL_LIGHT1, GL_SPECULAR, SPECULAR);
	glLightfv(GL_LIGHT1, GL_POSITION, POSITION1);

	x = 0;
	tecla = 0;
	paramCam = 0;
	paramFoc = 0;

	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, model_AMBIENT);
	glLightModeli(GL_LIGHT_MODEL_LOCAL_VIEWER, viewpoint);
	glLightModeli(GL_LIGHT_MODEL_TWO_SIDE, 1);

	glEnable(GL_LIGHT0);
	glEnable(GL_LIGHT1);
	glEnable(GL_LIGHTING);
	glEnable(GL_COLOR_MATERIAL);

	camUser[0] = -300;
	camUser[1] = 0;
	camUser[2] = 300;
	camUser[3] = 0;
	camUser[4] = 0;
	camUser[5] = 0;

	moviendoCam = false;
	poniendoFoc = false;
}

void ponReflex(int type)
{
	/*
		1 - Difusa
		2 - Difusa y Especular, Bajo Brillo
		3 - Difusa y Especular, Alto Brillo
		4 - Difusa y Emisi�n
		5 - Ambiente y Disufa
		6 - Ambiente, Difusa y Especular, Bajo Brillo
		7 - Ambiente, Difusa y Especular, Alto Brillo
		8 - Ambiente, Difusa y Emisi�n
		9 - Color Ambiente y Difusa
		10 - Color Ambiente, Difusa y Especular, Bajo Brillo
		11 - Color Ambiente, Difusa y Especular, Alto Brillo
		12 - Color Ambiente, Difusa y Emisi�n
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
	static int disqueRandom = 1;
	int lados = 4, a, b;
	int randMaterial = disqueRandom%12;//floor(rand() % 12) + 1;
	ponReflex(randMaterial);
	for (int i = 0; i < lados; i++)
	{
		a = i == 1 ? n - 1 : 0;
		b = i == 2 ? n - 1 : 0;
		for (int j = 0; j < n; j++)
		{
			int r = j % rows;//floor(rand() % rows);
			glColor3f(colores[r][0], colores[r][1], colores[r][2]);
			dibujaCubo(largo, largo * a, largo * b, 0);
			a = (i == 0 || i == 2) ? a + 1 : a;
			b = (i == 1 || i == 3) ? b + 1 : b;
		}
	}
	disqueRandom++;
}
void dibujaObra()
{
	glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

	glPushMatrix();
	glColor3f(1, 1, 0);
	dibujaEsfera(30, -5, -5, 0);

	glColor3f(1, 0, 1);
	dibujaEsfera(30, 450, -5, 0);

	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glColor4f(1, 0.5, 0.5, 0.5);
	dibujaPiramide(40, 60, -5, 450, 0);
	glDisable(GL_BLEND);

	glColor4f(0, 1, 1, 1);
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
		h += largo;
		largo -= cte;
		n -= 2;
	}

	glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT);
	//dibujaParedes(0.5);
}

void drawBitmapText(char* string, float x, float y, float z)
{
	char* c;
	glRasterPos3f(x, y, z);

	for (c = string; *c != 0; c++)
	{
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, *c);
	}
}

void visorInstrucciones()
{
	glDisable(GL_LIGHTING);
	glColor3f(1, 1, 1);
	const char* linea1 = "Bienvenido al Proyecto Final de Graficas por Computadora";
	const char* linea2 = "Instrucciones de interaccion de usuario";
	const char* linea3 = "Entre corchetes se encuentran los posibles valores";
	const char* linea22 = "En los pasos 2-7 despues del valor presione enter";


	const char* linea4 = "Para mover la camara es necesario lo siguiente:";
	const char* linea5 = "1. Presionar 'C'";
	const char* linea6 = "2. Escribir el primer parametro (xEye) [-500,500]";
	const char* linea7 = "3. Escribir el segundo parametro (yEye) [-500,500]";
	const char* linea8 = "4. Escribir el tercer parametro (zEye) [-500,500]";
	const char* linea9 = "5. Escribir el cuarto parametro (xRef) [-500,500]";
	const char* linea10 = "6. Escribir el quinto parametro (yRef) [-500,500]";
	const char* linea11 = "7. Escribir el sexto parametro (zRef) [-500,500]";

	const char* linea12 = "Si se equivoca pulse 'R' y comience de nuevo.";

	const char* linea13 = "Para poner un foco o cambiar su posicion y color:";
	const char* linea14 = "1. Presionar 'F'";
	const char* linea15 = "2. Escribir el primer parametro del color (R) [0,1]";
	const char* linea16 = "3. Escribir el segundo parametro del color (G) [0,1]";
	const char* linea17 = "4. Escribir el tercer parametro del color (B) [0,1]";
	const char* linea18 = "5. Escribir la primera coordenada del foco (x) [-500,500]";
	const char* linea19 = "6. Escribir la segunda coordenada del foco (y) [-500,500]";
	const char* linea20 = "7. Escribir la tercera coordenada del foco (z) [-500,500]";

	const char* linea21 = "Si se equivoca pulse 'R' y comience de nuevo.";

	drawBitmapText((char*)linea1, -300, 500, -1);
	drawBitmapText((char*)linea2, -300, 480, -1);
	drawBitmapText((char*)linea3, -300, 460, -1);
	drawBitmapText((char*)linea22, -300, 440, -1);
	drawBitmapText((char*)linea4, -300, 400, -1);
	drawBitmapText((char*)linea5, -300, 380, -1);
	drawBitmapText((char*)linea6, -300, 360, -1);
	drawBitmapText((char*)linea7, -300, 340, -1);
	drawBitmapText((char*)linea8, -300, 320, -1);
	drawBitmapText((char*)linea9, -300, 300, -1);
	drawBitmapText((char*)linea10, -300, 280, -1);
	drawBitmapText((char*)linea11, -300, 260, -1);
	drawBitmapText((char*)linea12, -300, 220, -1);
	drawBitmapText((char*)linea13, -300, 180, -1);
	drawBitmapText((char*)linea14, -300, 160, -1);
	drawBitmapText((char*)linea15, -300, 140, -1);
	drawBitmapText((char*)linea16, -300, 120, -1);
	drawBitmapText((char*)linea17, -300, 100, -1);
	drawBitmapText((char*)linea18, -300, 80, -1);
	drawBitmapText((char*)linea19, -300, 60, -1);
	drawBitmapText((char*)linea20, -300, 40, -1);
	drawBitmapText((char*)linea21, -300, 0, -1);

	gluLookAt(0, 0, 1, 0, 0, 0, 0, 1, 0);
	glEnable(GL_LIGHTING);
}

void visorAutomatico()
{
	int same = 300;
	gluLookAt(same*cos(x), same * sin(x), same, 0.0, 0.0, 0.0, 0.0, 1.0, 0);
	x += 0.0005;
	dibujaObra();
}

void visorUsuario()
{
	gluLookAt(camUser[0], camUser[1], camUser[2], camUser[3], camUser[4], camUser[5], 0, 1, 0);
	dibujaObra();
}

void pinta(void) {
	glClear(GL_COLOR_BUFFER_BIT);

	glViewport(0, 0, (2 * WINWIDTH) / 3, WINHEIGHT / 2);
	glLoadIdentity();
	visorUsuario();

	glViewport(0, WINHEIGHT / 2, (2 * WINWIDTH) / 3, WINHEIGHT / 2);
	glLoadIdentity();
	visorAutomatico();

	glViewport((2 * WINWIDTH) / 3, 0, WINWIDTH / 3, WINHEIGHT);
	glLoadIdentity();
	visorInstrucciones();

	glutSwapBuffers();
}

static void keyPressed(unsigned char key, int x, int y)
{
	teclas[tecla] = key;
	tecla++;
	if (key == 'R')
	{
		moviendoCam = false;
		paramCam = 0;
		poniendoFoc = 0;
		paramFoc = 0;
		for (int i = 0; i < tecla; i++)
			teclas[i] = 0;
		tecla = 0;
	}
	if (key == 'C') //movemos la camara del usuario
	{
		for (int i = 0; i < tecla; i++)
			teclas[i] = 0;
		tecla = 0;
		moviendoCam = true;
	}
	if (key == 'F') //Ponemos un tercer foco
	{
		for (int i = 0; i < tecla; i++)
			teclas[i] = 0;
		tecla = 0;
		poniendoFoc = true;
	}
	if (moviendoCam && key == 13)
	{
		const char* dato = (char*)teclas;
		auxCamUser[paramCam] = atof(dato);
		paramCam++;
		if (paramCam == 6)
		{
			paramCam = 0;
			moviendoCam = false;
			for (int i = 0; i < 6; i++)
				camUser[i] = auxCamUser[i];
			printf_s("Camara del usuario movida.\n");
		}
		for (int i = 0; i < tecla; i++)
			teclas[i] = 0;
		tecla = 0;
	}
	if (poniendoFoc && key == 13)
	{
		const char* dato = (char*)teclas;
		if (paramFoc < 3)
		{
			userColor[paramFoc] = atof(dato);
			paramFoc++;
		}
		else if(paramFoc < 6)
		{
			userPos[paramFoc - 3] = atof(dato);
			paramFoc++;
		}
		if(paramFoc == 6)
		{
			userColor[3] = 1;
			userPos[3] = 1;
			paramFoc = 0;
			poniendoFoc = false;
			glLightfv(GL_LIGHT2, GL_AMBIENT, userColor);
			glLightfv(GL_LIGHT2, GL_DIFFUSE, userColor);
			glLightfv(GL_LIGHT2, GL_SPECULAR, userColor);
			glLightfv(GL_LIGHT2, GL_POSITION, userPos);
			glEnable(GL_LIGHT2);
			printf_s("Tercer foco modificado. \n");
		}
		for (int i = 0; i < tecla; i++)
			teclas[i] = 0;
		tecla = 0;
	}
}

void reshapeFcn(GLint newWidth, GLint newHeight)
{
	WINWIDTH = newWidth;
	WINHEIGHT = newHeight;
	glMatrixMode(GL_PROJECTION);
	glFrustum(XWMIN, XWMAX, YWMIN, YWMAX, PNEAR, PFAR);
	glMatrixMode(GL_MODELVIEW);
	glClear(GL_COLOR_BUFFER_BIT);
}

int main(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(WINWIDTH, WINHEIGHT);
	glutCreateWindow("Proyecto Final");
	init();
	glutDisplayFunc(pinta);
	glutIdleFunc(pinta);
	glutReshapeFunc(reshapeFcn);
	glutKeyboardFunc(keyPressed);
	glutMainLoop();
	return 0;
}