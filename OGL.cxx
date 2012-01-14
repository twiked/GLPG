#include <GL/glut.h>
#include <math.h>
#include <iostream>
#include <sstream>

#include "transformations.h"

#define PI 3.1415926535897932

namespace
{
	//Variables de fenêtre.
	int x=0, y=0, w=800, h = 600;
	
	//Etat de l'animation
	bool move = false;
	
	//Matrice de travail
	GLfloat M[16];

	//Variables d'animation
	GLfloat i = 0, j = 0, speed_i = 0, speed_j = 0;
	
void affichage ()
{
	//Réinitialisation des tampons de pixel et de profondeur
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	//Définition de la matrice courante à GL_MODELVIEW
	glMatrixMode( GL_MODELVIEW );
	
	glLoadIdentity();
	
	//Positionement de la camera, qui en fait effectue la transformation inverse sur la scène.
	gluLookAt(0,0,-5,0,0,0,-1,0,0);
	
	//Les transformations
	glRotated(j, 0.7, 0.7, 0.5);
	CreateMatRotAxez(M, i);
	glMultMatrixf(M);
	glTranslatef(0.7,0.7,0.5);
	glScalef(0.4,0.4,0.4);
	
	//Dessin du cube
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
    
    //"Affichage" à l'écran
    glutSwapBuffers();
    glFlush();
	
}

//Fonction appellée lors du redimensionement de la fenêtre
void reshape(int width, int height)
{
	//Remplit la fenêtre avec le viewport
  	glViewport(0,0,width,height);
  	
  	//Définition de la perspective, qui doit l'être dans la matrice de projection
  	glMatrixMode(GL_PROJECTION);
  	glLoadIdentity();
  	//FOV de 70, ratio d'affichage correct, près=0.1, loin=100 (près < distance d'affichage < loin)
  	gluPerspective(70,float(width)/float(height),0.1,100); 
  	
  	glMatrixMode(GL_MODELVIEW);
}

//Fonction de callback appellée lors d'un appui de touche
void clavier(unsigned char key, int x, int y)
{
		switch (key)
		{
		case 32:
			//Si touche espace appuyée, activer/désactiver le mouvement
			move = move ? false : true;
		}
}

//Fonction similaire à celle ci-dessus, mais ne concerne que les caractères spéciaux
void clavier_special(int key, int x, int y)
{
	//Changement des deux vitesses de rotation avec les touches directionnelles
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
	
	//Affiche la vitesse courante en titre de fenêtre
	std::stringstream tit;
	tit << speed_i;
	glutSetWindowTitle(tit.str().c_str());
}

//Fonction callback de mouvement souris
void mouse(int xp, int yp)
{
	x = xp;
	y = yp;
	std::cout << x << "---" << y << std::endl;
}

//Fonction callback appellée lorsque le programme ne déssine pas
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
	
	//Initialisation de GLUT en Double-buffering, avec gestion de la profondeur
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGB);
	
	//Fenêtre positionnée à 50,50
	glutInitWindowPosition(50,50);
	
	//Fenêtre de taille w et h
	glutInitWindowSize(w,h);
	glutCreateWindow("Initialisation");
	
	//Activation de l'antialiasing, mais qui n'a pas l'air fonctionnel
	glHint(GL_POLYGON_SMOOTH_HINT, GL_NICEST);
	
	//Activation des test de Z-Buffer pour gestion de l'affichage avec profondeur, à ne pas confondre avec la perspective
	glEnable(GL_DEPTH_TEST);
	
	//Définition de la couleur de fond, gris
	glClearColor(0.5,0.5,0.5,1.0);
	
	glPointSize(1.0);
	
	//Définition de la perspective, qui doit l'être dans la matrice de projection
	glMatrixMode( GL_PROJECTION );
	glLoadIdentity();
	gluPerspective(70,(double)w/h,0,100);
	glMatrixMode( GL_MODELVIEW );

	//Définition des fonctions de callback à utiliser
	glutDisplayFunc(affichage);
	glutIdleFunc(idle);
	glutMotionFunc(mouse);
	glutKeyboardFunc(clavier);
	glutSpecialFunc(clavier_special);
	glutReshapeFunc(reshape);
	
	//Lancement du programme
	glutMainLoop();

}
