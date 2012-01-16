#include <GL/glut.h>
#include <math.h>
#include <iostream>
#include <sstream>

//Espace de nom inter-fichiers
namespace var
{
	//Doit-on utiliser les transformations natives de OpenGL ?
	bool native = true;
}
#include "transformations.h"

// definition de Pi, pour son utilisation dans le corps du programme
#define PI 3.1415926535897932

namespace
{
	//Variables de fenêtre.
	int x=0, y=0, w=800, h = 600, old_x=0, old_y=0;
	float eyedistance=-10, horizangle = 0, vertangle = 0;

	//Etat de l'animation
	bool move = false;
	
	//Variables pour le calcul de FPS
	unsigned long int frame=0, frame_t=0,time,timebase=0;
	float fps, moyenne;
	
	//Matrice de travail
	GLfloat M[16];

	//Variables d'animation -- vitesse de rotation
	GLfloat i = 0, j = 0, speed_i = 10, speed_j = 10;
	
void affichage ()
{
	
	frame++;
	frame_t++;
	time=glutGet(GLUT_ELAPSED_TIME);

	if (time - timebase > 1000) {
		//Calcul du nombre d'image lors de la dernière seconde
		fps = frame*1000.0/(time-timebase);
		
		//Définition du titre
		std::stringstream tit;
		tit << "OGL - " << fps << " FPS - Moyenne : " << frame_t*1000.0/time << native ? " - NATIF" : ;
		glutSetWindowTitle(tit.str().c_str());
		
		//Réinitialisation des compteurs de temps
	 	timebase = time;
		frame = 0;
	}

	//Réinitialisation des tampons de pixel et de profondeur
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	//Définition de la matrice courante à GL_MODELVIEW
	glMatrixMode( GL_MODELVIEW );
	
	//Chargement de la matrice identité
	glLoadIdentity();
	
	//Positionement de la camera, qui en fait effectue la transformation inverse sur la scène.
	gluLookAt(0,0,eyedistance,0,0,0,0,1,0);
	
	//Les transformations
	glRotated(horizangle, 0,1,0);
	glRotated(vertangle, 1, 0, 0);
	CreateMatRotAxez(M, i);
	//glTranslatef(0.7,0.7,0.4);
	CreateMatEch(M,0.4,0.4,0.4);
	
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
    
    //"Affichage réel" à l'écran
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
			break;
		}
}

//Fonction similaire à celle ci-dessus, mais ne concerne que les caractères spéciaux
void clavier_special(int key, int x, int y)
{
	//Rotation du cube avec les touches directionnelles
	switch (key)
	{
	case GLUT_KEY_UP:
			vertangle+=0.3;
			break;
	case GLUT_KEY_DOWN:
			vertangle-=0.3;
			break;
	case GLUT_KEY_RIGHT:
			horizangle+=0.3;
			break;
	case GLUT_KEY_LEFT:
			horizangle-=0.3;
			break;
	case GLUT_KEY_F1:
			//Active/désactive le mode natif
			var::native = (var::native) ? false : true;
			break;
	}
}

//Fonction callback de mouvement souris
void mouse(int button, int state, int xp, int yp)
{
	if (state == GLUT_UP)
	{
		//Roulette haut de souris -> zoom avant
		if (button == 3)
			eyedistance+=1;
		//Roulette bas de souris -> zoom arrière
		else if (button == 4)
			eyedistance-=1;
	}
	else
	{
		//Repositionne la position du clic de la souris pour éviter les 'sauts' du cube
		old_x = xp;
		old_y = yp;
	}
}

void mousemotion(int x, int y)
{
	//Changement de l'angle de rotation lorsque la souris se déplace
	horizangle+=(x-old_x);
	vertangle+=(y-old_y);
	old_x = x;
	old_y = y;
}

//Fonction callback appellée lorsque le programme ne déssine pas
void idle ()
{
	//Rotation automatique
	if (move)
	{
		horizangle+=speed_i/30;
		vertangle+=speed_j/30;
	}
	//Demande de réaffichage
	glutPostRedisplay();
}

} //namespace

int main (int argc, char * argv[])
{
	glutInit(&argc, argv);
	
	//Initialisation de GLUT en Double-buffering, avec gestion de la profondeur
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA | GLUT_MULTISAMPLE);
	
	//Fenêtre positionnée à 50,50
	glutInitWindowPosition(50,50);
	
	//Fenêtre de taille w et h
	glutInitWindowSize(w,h);
	glutCreateWindow("Initialisation");
	
	//Activation de l'antialiasing
	glHint(GL_POLYGON_SMOOTH_HINT, GL_NICEST);
	
	//Activation des test de Z-Buffer pour gestion de l'affichage avec profondeur, à ne pas confondre avec la perspective
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_BLEND);
        glEnable(GL_POLYGON_SMOOTH);
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
	//Fonctions de gestion du clavier-souris
	glutKeyboardFunc(clavier);
	glutSpecialFunc(clavier_special);
	glutMouseFunc(mouse);
	glutMotionFunc(mousemotion);
	//Fonction à appeler quand redimensionnement de la fenetre
	glutReshapeFunc(reshape);
	
	//Lancement du programme
	glutMainLoop();

}
