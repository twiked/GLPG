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
