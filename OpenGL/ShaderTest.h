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

private:
	GLuint m_program;
};