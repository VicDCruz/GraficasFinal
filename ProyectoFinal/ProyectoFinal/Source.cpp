#include <GL/glut.h>

static int width;
static int height;

static void pinta(void) {
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(1.0f, 0.0f, 0.0f);

	//Visor controlado por el usuario
	glViewport(0, 0, (2*width)/ 3, height / 2);
	glLoadIdentity();
	gluLookAt(0.0, 0.0, 0, 0, 0, -1.0, 0.0, 1.0, 0.0);

	glBegin(GL_QUADS);
	glVertex3d(-1, -1, 0);
	glVertex3d(-1, 1, 0);
	glVertex3d(1, 1, 0);
	glVertex3d(1, -1, 0);
	glEnd();

	//Visor automático
	glViewport(0, height/2, (2 * width) / 3, height / 2);
	glLoadIdentity();
	glColor3f(0, 0, 1);
	gluLookAt(0.0, 0.0, 0, 0, 0, -1.0, 0.0, 1.0, 0.0);

	glBegin(GL_QUADS);
	glVertex3d(-1, -1, 0);
	glVertex3d(-1, 1, 0);
	glVertex3d(1, 1, 0);
	glVertex3d(1, -1, 0);
	glEnd();

	//Visor de instrucciones
	glViewport((2 * width) / 3, 0, width / 3, height);
	glLoadIdentity();
	glColor3f(0, 1, 0.0f);
	gluLookAt(0.0, 0.0, 0, 0, 0, -1.0, 0.0, 1.0, 0.0);

	glBegin(GL_QUADS);
	glVertex3d(-1, -1, 0);
	glVertex3d(-1, 1, 0);
	glVertex3d(1, 1, 0);
	glVertex3d(1, -1, 0);
	glEnd();


	glFlush();
}

static void reshape(int w, int h) {
	width = w;
	height = h;
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glFrustum(-1.0, 1.0, -1.0, 1.0, 0, 20.0);
	glMatrixMode(GL_MODELVIEW);
}

int main(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(500, 500);
	glutInitWindowPosition(100, 100);
	glutCreateWindow(argv[0]);
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glShadeModel(GL_FLAT);
	glutDisplayFunc(pinta);
	glutReshapeFunc(reshape);
	glutMainLoop();
	return 0;
}