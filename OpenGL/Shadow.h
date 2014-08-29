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
	//����һ����ӰͶӰ���󣬸���ƽ�淽�̵�ϵ���Լ����յ�λ�ô�����
	//�洢��mat��
	M3DMatrix44f shadowMat;
	static GLfloat lightPos[4];
};