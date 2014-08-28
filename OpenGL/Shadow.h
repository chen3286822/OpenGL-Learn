#pragma once

#include "OpenGL.h"

class ShadowTest : public OpenGLTest
{
public:
	CreateTest(ShadowTest);
	virtual void init(void);
	virtual void display(void);
	virtual void reshape(GLint w, GLint h);
private:
	//创建一个阴影投影矩阵，根据平面方程的系数以及光照的位置创建的
	//存储在mat中
	void makeShadowMatrix(GLfloat* vPoints[3], GLfloat* lightPos, GLfloat* mat);
};