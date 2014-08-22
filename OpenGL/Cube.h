#pragma once

#include "OpenGL.h"

class CubeTest: public OpenGLTest
{
public:
	CreateTest(CubeTest);
	virtual void init(void);
	virtual void display(void);
	virtual void reshape(GLint w, GLint h);
};