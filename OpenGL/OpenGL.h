#pragma once

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

class OpenGLTest
{
public:
	CreateTest(OpenGLTest);
	virtual void init(void);
	virtual void display(void);
	virtual void reshape(GLint w, GLint h);
};

extern OpenGLTest* g_Test;