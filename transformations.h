#include <cstring>

#define NATIVE true

GLfloat * CreateMatEch (GLfloat* M, GLfloat x, GLfloat y, GLfloat z)
{
	if (NATIVE)
		glScalef(x,y,z);
	else
		{
		GLfloat L[] =
	{ x,   0.0, 0.0, 0.0,
	  0.0, y,   0.0, 0.0,
	  0.0, 0.0, z,   0.0,
	  0.0, 0.0, 0.0, 1.0};
		glMultMatrixf(L);
		}
}

GLfloat* CreateMatRotx (GLfloat* M, GLfloat angle)
{
	if (NATIVE)
		glRotatef(angle, 1,0,0);
	else
		{
		GLfloat L[] =
	{ 1.0,  0.0,         0.0,          0.0,
	  0.0,  cosf(angle), sinf(angle),  0.0,
	  0.0,  -sinf(angle),cosf(angle),  0.0,
	  0.0,  0.0,         0.0,          1.0};
		glMultMatrixf(L);
		}
};

GLfloat* CreateMatRotz (GLfloat* M, GLfloat angle)
{
	if (NATIVE)
		glRotatef(angle, 0,1,0);
	else
		{
		GLfloat L[] =
	{ cosf(angle),  sinf(angle),  0.0, 0.0,
	  -sinf(angle), cosf(angle),  0.0, 0.0,
	  0.0,          0.0,          1.0, 0.0,
	  0.0,          0.0,          0.0, 1.0};
		glMultMatrixf(L);
		}
};

void CreateMatRoty (GLfloat* M, GLfloat angle)
{
	if (NATIVE)
		glRotatef(angle, 0,0,1);
	else
		{
		GLfloat L[] =
	{ cosf(angle),  0.0, -sinf(angle), 0.0,
	  0.0,          1.0, 0.0,          0.0,
	  sinf(angle),  0.0, cosf(angle),  0.0,
	  0.0,          0.0, 0.0,          1.0};
		glMultMatrixf(L);
		}
};

GLfloat* CreateMatTransVec (GLfloat* M, GLfloat Tx, GLfloat Ty, GLfloat Tz)
{
	if (NATIVE)
		glTranslatef(Tx,Ty,Tz);
	else
		{
		GLfloat L[] =
	{ 1.0, 0.0, 0.0, 0.0,
	  0.0, 1.0, 0.0, 0.0,
	  0.0, 0.0, 1.0, 0.0,
	  Tx,  Ty,  Tz,  1.0};
		glMultMatrixf(L);
	}
}

void CreateMatRotAxez (GLfloat* M, GLfloat angle)
{
	GLfloat L[] =
{ (3 + cos (angle)),  				(sqrtf(3) * (-cos (angle) + 1)), 	(-2 * sin (angle)), 			0.0,
  (sqrtf(3) * (-cos (angle) + 1)), 	(3 * cos(angle) +1), 				(2* sqrtf(3) * sin(angle)), 	0.0,
  (2 * sin (angle)), 					(-2 * sqrtf(3) * sin(angle)), 	(4 * cos(angle)), 			0.0,
  0.0,  								0.0,  								0.0,  							4.0};
	glMultMatrixf(L);
}

/*GLfloat* CreateMatTransAngz (GLfloat angle, )
{
	GLfloat M[] =
{ 1.0, 0.0, 0.0, Tx,
  0.0, 1.0, 0.0, Ty,
  0.0, 0.0, 1.0, 0.0,
  0.0, 0.0, 0.0, 1.0};
}*/
