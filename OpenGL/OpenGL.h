#pragma once

#define CHECK_GL_ERROR_DEBUG() \
do {\
GLenum __error = glGetError(); \
if (__error) {\
	std::cout << "OpenGL error 0x" << __error << " in " << __FILE__ << " " << __FUNCTION__ << " " << __LINE__ << std::endl; \
} \
} while (false)

#define CreateTest(type) \
	static type* create() \
{ \
	type *pRet = new type(); \
	return pRet; \
}


enum class TestType
{
	Basic,
	ArrayBuffer,
	CullFace,
	RecursiveSubdivision,
	EdgeFlag,
	SimpleDraw,
	StrippleLine,
	VertexArray,
};

void gTimer(GLint value);

class OpenGLTest
{
public:
	virtual ~OpenGLTest(){}

	CreateTest(OpenGLTest);
	virtual void init(void);
	virtual void display(void);
	virtual void reshape(GLint w, GLint h);
	virtual void keyboard(GLubyte key, GLint x, GLint y);
	virtual void timer(GLint value);
};

extern OpenGLTest* g_Test;