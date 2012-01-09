#include <GL/glut.h>
#include <math.h>

#define PI 3.1415926535897932

namespace
{

	GLfloat i = PI/6;
	GLfloat j = PI/6;
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
	glutSwapBuffers();
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
  0.0,  cosf(angle), sinf(angle),  0.0,
  0.0,  -sinf(angle),cosf(angle),  0.0,
  0.0,  0.0,         0.0,          1.0};
	return M;
};

GLfloat* CreateMatRotz (GLfloat angle)
{
	GLfloat M[] =
{ cosf(angle),  sinf(angle),  0.0, 0.0,
  -sinf(angle), cosf(angle),  0.0, 0.0,
  0.0,          0.0,          1.0, 0.0,
  0.0,          0.0,          0.0, 1.0};
	return M;
};

GLfloat* CreateMatRoty (GLfloat angle)
{
	GLfloat M[] =
{ cosf(angle),  0.0, -sinf(angle), 0.0,
  0.0,          1.0, 0.0,          0.0,
  sinf(angle),  0.0, cosf(angle),  0.0,
  0.0,          0.0, 0.0,          1.0};
	return M;
};

GLfloat* CreateMatTransVec (GLfloat Tx, GLfloat Ty, GLfloat Tz)
{
	GLfloat M[] =
{ 1.0, 0.0, 0.0, 0.0,
  0.0, 1.0, 0.0, 0.0,
  0.0, 0.0, 1.0, 0.0,
  Tx,  Ty,  Tz,  1.0};
	return M;
}

GLfloat* CreateMatRotAxez (GLfloat angle)
{
	GLfloat M[] =
{ (3 + cos (angle))/4,  				(sqrtf(3) * (-cos (angle) + 1))/4, 	(-2 * sin (angle))/4, 			0.0,
  (sqrtf(3) * (-cos (angle) + 1))/4, 	(3 * cos(angle) +1)/4, 				(2* sqrtf(3) * sin(angle))/4, 	0.0,
  (2 * sin (angle))/4, 					(-2 * sqrtf(3) * sin(angle))/4, 	(4 * cos(angle))/4, 			0.0,
  0.0,  								0.0,  								0.0,  							1.0};
	return M;
}

/*GLfloat* CreateMatTransAngz (GLfloat angle, )
{
	GLfloat M[] =
{ 1.0, 0.0, 0.0, Tx,
  0.0, 1.0, 0.0, Ty,
  0.0, 0.0, 1.0, 0.0,
  0.0, 0.0, 0.0, 1.0};
}*/

void idle ()
{
	//glLoadIdentity();
	j+=0.005;
	i+=0.005;
	glLoadMatrixf(CreateMatEch(0.7,0.7,0));
	glMultMatrixf(CreateMatTransVec(0.433,0.25,0));
	//glMultMatrixf(CreateMatRotz(j));
	glMultMatrixf(CreateMatRotAxez(i));
	//glMultMatrixf();
	glutPostRedisplay();

}
}

int main (int argc, char * argv[])
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);
	glutInitWindowPosition(200,200);
	glutInitWindowSize(250,250);
	glutCreateWindow("ogl1");

	glClearColor(0.5,0.5,0.5,0.0);
	glPointSize(2.0);

	glutDisplayFunc(affichage);
	glutIdleFunc(idle);
	//glutKeyboardFunc(clavier);

	glutMainLoop();


}
