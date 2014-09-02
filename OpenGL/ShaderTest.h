#pragma once

#include "OpenGL.h"

class ShaderTest : public OpenGLTest
{
public:
	virtual ~ShaderTest();
	CreateTest(ShaderTest);
	virtual void init(void);
	virtual void display(void);
	virtual void reshape(GLint w, GLint h);
	virtual void keyboard(GLubyte key, GLint x, GLint y);

private:
	GLuint m_program;

	static GLfloat cube[8][3];
	static GLbyte index[12][3];

	GLfloat angle;
};