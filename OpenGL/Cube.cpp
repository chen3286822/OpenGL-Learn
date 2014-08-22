#include "stdafx.h"
#include "Cube.h"

void CubeTest::init(void)
{
	glewInit();
	glClearColor(0.0, 0.0, 0.0, 0.0);/* select clearing color   */
	//��ɫģʽ��GL_SMOOTHʹ�ò�ֵ��ʽ��ɫ��GL_FLATʹ�ö�����ɫ���������������ɫ��ɫ
	glShadeModel(GL_FLAT);
}

void CubeTest::reshape(GLint w, GLint h)
{
	//���ֻ��Ƴ���������Σ���ʼ��λ�ڴ��ڵ�����
	GLint newW = w > h ? h : w;
	glViewport((w-newW)/2, (h-newW)/2, (GLsizei)newW, (GLsizei)newW);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	//glFrustum(-1.0, 1.0, -1.0, 1.0, 1.5, 20);
	gluPerspective(60.0, 1.0, 1.5, 20);
	//glOrtho(-10.0, 10.0, -10.0, 10.0, 1.5, 20);
	glMatrixMode(GL_MODELVIEW);
}

void CubeTest::display()
{
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(1.0, 1.0, 1.0);
	glLoadIdentity();
	gluLookAt(0.0, 0.0, 10.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);

	//����������б任������x���ƶ�5������z����ʱ����ת30��
	//ģ�ͱ任����Ϊ C��ÿ�α任���൱��C*M, C*M*N
	//���Ӧ�õ�ģ�Ͷ����ϣ�C*M*N*v���൱��C*(M*(N*v))
	//��ʵ�Ǳ任N��Ӧ���ڶ���v����ʵ�ʵ��ñ任������˳������Ҫʵ�ֵı任���෴��
	glRotatef(30.0, 0.0, 0.0, 1.0);
	glTranslatef(5.0, 0.0, 0.0);
	glutWireCube(1.0);

	//��һ����������һ������ת45��
	glLoadIdentity();
	gluLookAt(0.0, 0.0, 10.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
	glTranslatef(3.0, 0.0, 0.0);
	glRotatef(45.0, 0.0, 0.0, 1.0);
	glTranslatef(-3.0, 0.0, 0.0);
	glBegin(GL_TRIANGLES);
	glVertex3f(0.0, 0.0, 0.0);
	glVertex3f(3.0, 0.0, 0.0);
	glVertex3f(3.0, 3.0, 0.0);
	glEnd();

	glFlush();
}