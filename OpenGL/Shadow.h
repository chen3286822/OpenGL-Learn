#pragma once

#include "OpenGL.h"

class ShadowTest : public OpenGLTest
{
public:
	CreateTest(ShadowTest);
	virtual void init(void);
	virtual void display(void);
private:
	//����һ����ӰͶӰ���󣬸���ƽ�淽�̵�ϵ���Լ����յ�λ�ô�����
	//�洢��mat��
	void makeShadowMatrix(GLfloat* vPoints[3], GLfloat* lightPos, GLfloat* mat);
};