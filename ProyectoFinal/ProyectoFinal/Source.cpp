#include <GL/glut.h>

static int width;
static int height;
static void visorUsuario();
static void visorAutomatico();
static void visorInstrucciones();

static void pinta(void) {
	glClear(GL_COLOR_BUFFER_BIT);

	//Visor controlado por el usuario
	glViewport(0, 0, (2*width)/ 3, height / 2);
	visorUsuario();

	//Visor automático
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
	glLoadIdentity();
	glColor3f(1.0f, 0.0f, 0.0f);
	gluLookAt(0.0, 0.0, 0, 0, 0, -1.0, 0.0, 1.0, 0.0);

	glBegin(GL_QUADS);
	glVertex3d(-1, -1, 0);
	glVertex3d(-1, 1, 0);
	glVertex3d(1, 1, 0);
	glVertex3d(1, -1, 0);
	glEnd();
}

static void visorAutomatico()
{
	glLoadIdentity();
	glColor3f(0, 0, 1);
	gluLookAt(0.0, 0.0, 0, 0, 0, -1.0, 0.0, 1.0, 0.0);

	glBegin(GL_QUADS);
	glVertex3d(-1, -1, 0);
	glVertex3d(-1, 1, 0);
	glVertex3d(1, 1, 0);
	glVertex3d(1, -1, 0);
	glEnd();
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
	glutInitWindowSize(600, 600);
	glutInitWindowPosition(100, 100);
	glutCreateWindow(argv[0]);
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glShadeModel(GL_FLAT);
	glutDisplayFunc(pinta);
	glutReshapeFunc(reshape);
	glutMainLoop();
	return 0;
}