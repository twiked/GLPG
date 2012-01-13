#include <GL/glut.h>
#include <math.h>
#include <iostream>
#include <sstream>

#include "transformations.h"

#define PI 3.1415926535897932
namespace
{
	int x=0, y=0, w=800, h = 600;
	bool move = false;
	GLfloat M[16];

	GLfloat i = 0, j = 0, speed_i = 0, speed_j = 0;
void affichage ()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT) ;
	glMatrixMode( GL_MODELVIEW );
	glLoadIdentity();
	gluLookAt(0,0,-5,0,0,0,-1,0,0);
	glScalef(0.4,0.4,0.4);
	glTranslatef(0.7,0.7,0.5);
	CreateMatRotAxez(M, i);
	glMultMatrixf(M);
	
	//glRotated(i, 0, 0, 1);
	glRotated(j, 0.7, 0.7, 0.5);
	
	glBegin(GL_QUADS);

    glColor3ub(255,0,0); //face rouge
		glVertex3d(1,1,1);
		glVertex3d(1,1,-1);
		glVertex3d(-1,1,-1);
		glVertex3d(-1,1,1);

    glColor3ub(0,255,0); //face verte
		glVertex3d(1,-1,1);
		glVertex3d(1,-1,-1);
		glVertex3d(1,1,-1);
		glVertex3d(1,1,1);

    glColor3ub(0,0,255); //face bleue
		glVertex3d(-1,-1,1);
		glVertex3d(-1,-1,-1);
		glVertex3d(1,-1,-1);
		glVertex3d(1,-1,1);

    glColor3ub(255,255,0); //face jaune
		glVertex3d(-1,1,1);
		glVertex3d(-1,1,-1);
		glVertex3d(-1,-1,-1);
		glVertex3d(-1,-1,1);

    glColor3ub(0,255,255); //face cyan
		glVertex3d(1,1,-1);
		glVertex3d(1,-1,-1);
		glVertex3d(-1,-1,-1);
		glVertex3d(-1,1,-1);

    glColor3ub(255,0,255); //face magenta
		glVertex3d(1,-1,1);
		glVertex3d(1,1,1);
		glVertex3d(-1,1,1);
		glVertex3d(-1,-1,1);

    glEnd();
    glutSwapBuffers();
    glFlush();
	
}

void reshape(int width, int height)
{ 	 
  	glViewport(0,0,width,height);
  	glMatrixMode(GL_PROJECTION);
  	glLoadIdentity();
  	gluPerspective(70,float(width)/float(height),0.1,100); 
  	glMatrixMode(GL_MODELVIEW);
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
	std::stringstream tit;
	tit << speed_i;
	glutSetWindowTitle(tit.str().c_str());
}
void mouse(int xp, int yp)
{
	x = xp;
	y = yp;
	std::cout << x << "---" << y << std::endl;
}

void idle ()
{
	i+=speed_i/300;
	j+=speed_j/300;
	glutPostRedisplay();
}
} //namespace

int main (int argc, char * argv[])
{

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowPosition(50,50);
	glutInitWindowSize(w,h);
	glutCreateWindow("ogl1");
	glHint(GL_POLYGON_SMOOTH_HINT, GL_NICEST);
	glEnable(GL_DEPTH_TEST);
	glClearColor(0.5,0.5,0.5,1.0);
	glPointSize(1.0);

	glMatrixMode( GL_PROJECTION );
	glLoadIdentity();
	gluPerspective(70,(double)w/h,0,100);
	glMatrixMode( GL_MODELVIEW );

	glutDisplayFunc(affichage);
	glutIdleFunc(idle);
	glutMotionFunc(mouse);
	glutKeyboardFunc(clavier);
	glutSpecialFunc(clavier_special);
	glutReshapeFunc(reshape);
	glutMainLoop();

}