#include <GL/glut.h>
#include <math.h>
#include <iostream>

#define PI 3.1415926535897932

namespace
{
	int x=0, y=0, w=250, h = 250;
	bool move = false;

	GLfloat i = PI/6, j = PI/6, speed_i = 20, speed_j = 20;
void affichage ()
{
	GLbitfield masque = GL_COLOR_BUFFER_BIT;
	glClear(masque);


	glBegin(GL_QUADS);
	glColor3f(1.0, 0.0, 1.0);
	glVertex3f(0.0, 0.0, 0.0);
	//glColor3f(1.0, 1.0, 0.0);
	glVertex3f(1.0, 0.0, 0.0);
	//glColor3f(0.0, 1.0, 1.0);
	glVertex3f(1.0, 1.0, 0.0);
	//glColor3f(1.0, 0.0, 1.0);
	glVertex3f(0.0, 1.0, 0.0);
	//glEnd();

	//glBegin(GL_QUADS);
	glColor3f(0.0, 0.0, 1.0);
	glVertex3f(0.0, 0.0, 1.0);
	//glColor3f(1.0, 1.0, 0.0);
	glVertex3f(1.0, 0.0, 1.0);
	//glColor3f(0.0, 1.0, 1.0);
	glVertex3f(1.0, 1.0, 1.0);
	//glColor3f(1.0, 0.0, 1.0);
	glVertex3f(0.0, 1.0, 1.0);
	//glEnd();

	//glBegin(GL_POLYGON);
	glColor3f(1.0, 0.0, 0.0);
	glVertex3f(0.0, 0.0, 0.0);
	//glColor3f(1.0, 1.0, 0.0);
	glVertex3f(0.0, 1.0, 0.0);
	//glColor3f(0.0, 1.0, 1.0);
	glVertex3f(0.0, 1.0, 1.0);
	//glColor3f(1.0, 0.0, 1.0);
	glVertex3f(0.0, 0.0, 1.0);
	//glEnd();

	//glBegin(GL_POLYGON);
	glColor3f(0.0, 1.0, 0.0);
	glVertex3f(0.0, 0.0, 0.0);
	//glColor3f(1.0, 1.0, 0.0);
	glVertex3f(1.0, 0.0, 0.0);
	//glColor3f(0.0, 1.0, 1.0);
	glVertex3f(1.0, 0.0, 1.0);
	//glColor3f(1.0, 0.0, 1.0);
	glVertex3f(0.0, 0.0, 1.0);
	//glEnd();

	//glBegin(GL_POLYGON);
	glColor3f(0.0, 1.0, 1.0);
	glVertex3f(1.0, 1.0, 0.0);
	//glColor3f(1.0, 1.0, 0.0);
	glVertex3f(1.0, 0.0, 0.0);
	//glColor3f(0.0, 1.0, 1.0);
	glVertex3f(1.0, 0.0, 1.0);
	//glColor3f(1.0, 0.0, 1.0);
	glVertex3f(1.0, 1.0, 1.0);
	//glEnd();

	//glBegin(GL_POLYGON);
	glColor3f(1.0, 1.0, 0.0);
	glVertex3f(0.0, 1.0, 0.0);
	//glColor3f(1.0, 1.0, 0.0);
	glVertex3f(1.0, 1.0, 0.0);
	//glColor3f(0.0, 1.0, 1.0);
	glVertex3f(1.0, 1.0, 1.0);
	//glColor3f(1.0, 0.0, 1.0);
	glVertex3f(0.0, 1.0, 1.0);
	glEnd();
	glutSwapBuffers();
}

void reshape(int width, int height)
{
	w = width;
	h = height;
	if (x<y)
		glViewport(0,(h-w)/2,w,w);
	else
		glViewport((w-h)/2,0,h,h);
}

void clavier(unsigned char key, int x, int y)
{
		switch (key)
		{
		case 32:
			move = move ? false : true;
		}
}

void clavier_special(int key, int x, int y)
{
	switch (key)
	{
	case GLUT_KEY_UP:
		speed_i+=1;
		break;
	case GLUT_KEY_DOWN:
			speed_i-=1;
			break;
	case GLUT_KEY_RIGHT:
			speed_j+=1;
			break;
	case GLUT_KEY_LEFT:
			speed_j+=1;
			break;
	}
	std::cout << "COOL" << std::endl;
}
void mouse(int xp, int yp)
{
	x = xp;
	y = yp;
	std::cout << x << "---" << y << std::endl;
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
	glLoadIdentity();
	glLoadMatrixf(CreateMatEch(0.4,0.4,0));
	glMultMatrixf(CreateMatTransVec(0.433,0.25,0));
	if (move)
	{
//	gluLookAt(	0.f, 0.f, 0.f,
//				0.f, 0.f,    0.f,
//				0.f, 0.f,  1.f);
	i+=0.005*speed_i/20;
	j+=0.005*speed_j/20;
	//glMultMatrixf(CreateMatRotz(j));

	//glMultMatrixf();
	}
	glMultMatrixf(CreateMatRotAxez(i));
	glutPostRedisplay();
}
} //namespace

int main (int argc, char * argv[])
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowPosition(200,200);
	glutInitWindowSize(250,250);
	glutCreateWindow("ogl1");

	glHint(GL_POLYGON_SMOOTH_HINT, GL_NICEST);

	glClearColor(0.5,0.5,0.5,1.0);
	glPointSize(2.0);

	glutDisplayFunc(affichage);
	glutIdleFunc(idle);
	glutMotionFunc(mouse);
	glutKeyboardFunc(clavier);
	glutSpecialFunc(clavier_special);
	glutReshapeFunc(reshape);
	glutMainLoop();


}
