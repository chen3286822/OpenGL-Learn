#include "stdafx.h"
#include "Shadow.h"

GLfloat ShadowTest::lightPos[4] = { 0, 100, 0, 1 };

void ShadowTest::init(void)
{
	glewInit();
	glClearColor(0.0, 0.0, 0.0, 0.0);/* select clearing color   */
	glShadeModel(GL_SMOOTH);
	glEnable(GL_DEPTH_TEST);
	glFrontFace(GL_CCW);
	glEnable(GL_CULL_FACE);
	glEnable(GL_LIGHTING);

	GLfloat ambientLight[] = { 0.2, 0.2, 0.2, 1.0 };
	//ʹ��΢�������⣬ʹ����ɼ�
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, ambientLight);

	GLfloat specular[] = { 1.0, 1.0, 1.0, 1.0 };
	GLfloat spotDir[] = { 0, -1, 0, 0 };
	
	GLfloat specref[] = { 1, 1, 1, 1 };
	glLightfv(GL_LIGHT0, GL_SPECULAR, specular);
	glLightfv(GL_LIGHT0, GL_SPOT_DIRECTION, spotDir);
	glLightf(GL_LIGHT0, GL_SPOT_CUTOFF, 85.0f);
	glLightfv(GL_LIGHT0, GL_POSITION, lightPos);
	glEnable(GL_LIGHT0);

	//������ɫ׷��
	glEnable(GL_COLOR_MATERIAL);
	//���������Ĳ��ʻ�����ɢ����ɫ��׷��glColor
	glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);
	//���ò��ʾ��淴������
	glMaterialfv(GL_FRONT, GL_SPECULAR, specref);
	//���þ��������С�ͼ���ֵ
	glMateriali(GL_FRONT, GL_SHININESS, 50);

	//ȡ3��ƽ���ϵĵ�
	M3DVector3f points[3] = { { -100, -100, -100 },
	{ -100, -100, 100 },
	{ 100, -100, 100 } };

	M3DVector4f vPlaneEquation;
	//ȡ��ƽ�淽��
	m3dGetPlaneEquation(vPlaneEquation, points[0], points[1], points[2]);
	//���ݹ�Դλ�á�ƽ�淽�̵ó���Ӱ����
	m3dMakePlanarShadowMatrix(shadowMat, vPlaneEquation, lightPos);
}

void ShadowTest::reshape(GLint w, GLint h)
{
	//���ֻ��Ƴ���������Σ���ʼ��λ�ڴ��ڵ�����
	GLint newW = w > h ? h : w;
	glViewport((w - newW) / 2, (h - newW) / 2, (GLsizei)newW, (GLsizei)newW);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	//glFrustum(-1.0, 1.0, -1.0, 1.0, 1.5, 20);
	gluPerspective(60.0, 1.0, 1.5, 350);
	//glOrtho(-10.0, 10.0, -10.0, 10.0, 1.5, 20);
	
}

void ShadowTest::display(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);/* clear all pixels   */
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(0.0, 50.0, 300.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);

	//���ù���
	glEnable(GL_LIGHTING);
	glLightfv(GL_LIGHT0, GL_POSITION, lightPos);

	//����һ��СԲ������Դ
	glPushMatrix();
	glTranslatef(lightPos[0], lightPos[1], lightPos[2]);
	glColor3f(1, 1, 0);
	glutSolidSphere(5, 10, 10);
	glPopMatrix();

	//����
	glColor3f(1.0, 1.0, 1.0);
	glBegin(GL_QUADS);
	glNormal3f(0, 1, 0);
	glVertex3f(-100, -100, -100);
	glVertex3f(-100, -100, 100);
	glVertex3f(100, -100, 100);
	glVertex3f(100, -100, -100);
	glEnd();

	glutSolidSphere(50, 50, 50);

	//���ù��գ�������Ӱ
	glDisable(GL_LIGHTING);
	//������Ȳ��ԣ���Ϊ��Ӱ����Ƶ������ϣ�������Ӱ�����
	glDisable(GL_DEPTH_TEST);
	//�������״̬
	glPushMatrix();

	//������Ӱ����
	glMultMatrixf((GLfloat*)shadowMat);
	//��Ӱ��ɫ
	glColor3f(0, 0, 0);
	//����������Ӱ
	glutSolidSphere(50, 50, 50);
	//�ָ�����
	glPopMatrix();

	//�ָ���Ȳ���
	glEnable(GL_DEPTH_TEST);

	glFlush();
	glutSwapBuffers();
}