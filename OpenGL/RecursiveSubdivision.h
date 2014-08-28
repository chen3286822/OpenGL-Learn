#pragma once

#include "OpenGL.h"

class RecursiveSubdivisionTest : public OpenGLTest
{
public:
	CreateTest(RecursiveSubdivisionTest);
	virtual void init(void);
	virtual void display(void);
	virtual void reshape(GLint w, GLint h);
	virtual void keyboard(GLubyte key, GLint x, GLint y);
private:
	void normalizeToRadius(GLfloat* v, GLfloat r = 1.0f);
	void computeNormal(GLfloat* v1, GLfloat* v2, GLfloat* v3, GLfloat* norm);
	void drawTriangle(GLfloat* v1, GLfloat* v2, GLfloat* v3);
	void subDivision(GLfloat* v1, GLfloat* v2, GLfloat* v3, GLint depth);
};