#include <GL/glut.h>
#include <math.h>
void affichage ()
{
	GLbitfield masque = GL_COLOR_BUFFER_BIT;
	glClear(masque);

	glColor3f(1.0, 1.0, 1.0);

	glBegin(GL_POLYGON);
	glVertex3f(0.5, 0.5, 0.0);
	glColor3f(1.0, 1.0, 0.0);
	glVertex3f(0.5, -0.5, 0.0);
	glColor3f(0.0, 1.0, 1.0);
	glVertex3f(-0.5, -0.5, 0.0);
	glColor3f(1.0, 0.0, 1.0);
	glVertex3f(-0.5, 0.5, 0.0);
	glEnd();

	glFlush();
}

GLfloat * CreateMatEch (GLfloat x, GLfloat y, GLfloat z)
{
	GLfloat M[] =
{ x,   0.0, 0.0, 0.0,
  0.0, y,   0.0, 0.0,
  0.0, 0.0, z,   0.0,
  0.0, 0.0, 0.0, 1.0};
	return M;
}

GLfloat* CreateMatRotx (GLfloat angle)
{
	GLfloat M[] =
{ 1.0,  0.0,         0.0,          0.0,
  0.0,  cosf(angle), -sinf(angle), 0.0,
  0.0,  sinf(angle), cosf(angle),  0.0,
  0.0,  0.0,         0.0,          1.0};
	return M;
};

GLfloat* CreateMatRotz (GLfloat angle)
{
	GLfloat M[] =
{ cosf(angle),  -sinf(angle), 0.0, 0.0,
  sinf(angle),  cosf(angle),  0.0, 0.0,
  0.0,          0.0,          1.0, 0.0,
  0.0,          0.0,          0.0, 1.0};
	return M;
};

GLfloat* CreateMatRoty (GLfloat angle)
{
	GLfloat M[] =
{ cosf(angle),  0.0,         sinf(angle),          0.0,
  0.0,          1.0, 0.0, 0.0,
  -sinf(angle), 0.0, cosf(angle),  0.0,
  0.0,          0.0,         0.0,          1.0};
	return M;
};

void idle ()
{
	static float i;
	glLoadIdentity();
	glLoadMatrixf(CreateMatRotz(i += 10));
	//glMultMatrixf();
	glutPostRedisplay();
}

int main (int argc, char * argv[])
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB);
	glutInitWindowPosition(200,200);
	glutInitWindowSize(250,250);
	glutCreateWindow("ogl1");

	glClearColor(0.8,0.8,0.8,0.8);
	glPointSize(2.0);

	glutDisplayFunc(affichage);
	glutIdleFunc(idle);
	//glutKeyboardFunc(clavier);

	glutMainLoop();


}
