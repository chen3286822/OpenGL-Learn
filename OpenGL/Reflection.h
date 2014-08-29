#pragma once

#include "OpenGL.h"

class ReflectionTest : public OpenGLTest
{
public:
	CreateTest(ReflectionTest);
	virtual void init(void);
	virtual void display(void);
	virtual void reshape(GLint w, GLint h);

private:
	static GLfloat fLightPos[4];
	static GLfloat fLightPosMirror[4];
};