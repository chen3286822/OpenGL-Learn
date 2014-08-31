#pragma once

#include "OpenGL.h"

class FogTest : public OpenGLTest
{
public:
	CreateTest(FogTest);
	virtual void init(void);
	virtual void display(void);
	virtual void reshape(GLint w, GLint h);
private:
	void drawSphere(GLfloat* pos);
	M3DMatrix44f shadowMat;
};