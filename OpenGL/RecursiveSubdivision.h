#pragma once

#include "OpenGL.h"

class RecursiveSubdivisionTest : public OpenGLTest
{
public:
	CreateTest(RecursiveSubdivisionTest);
	virtual void init(void);
	virtual void display(void);
	virtual void reshape(GLint w, GLint h);
private:
	void normalize10(GLfloat* v);
	void drawTriangle(GLfloat* v1, GLfloat* v2, GLfloat* v3);
	void subDivision(GLfloat* v1, GLfloat* v2, GLfloat* v3, GLint depth);
};