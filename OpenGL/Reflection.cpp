#include "stdafx.h"
#include "Reflection.h"

GLfloat ReflectionTest::fLightPos[4] = {0, 150, 0, 1};
GLfloat ReflectionTest::fLightPosMirror[4] = {0, -150, 0, 1};

void ReflectionTest::init(void)
{
	glewInit();
	glClearColor(0.0, 0.0, 0.0, 0.0);

	glEnable(GL_DEPTH_TEST);
	glFrontFace(GL_CCW);
	glCullFace(GL_BACK);
	glEnable(GL_CULL_FACE);

	GLfloat ambient[] = { 0.0f, 0.0f, 0.0f, 0.0f };
	GLfloat diffuse[] = { 0.25f, 0.25f, 0.25f, 1.0f };
	GLfloat specular[] = { 1.0f, 1.0f, 1.0f, 1.0f };
	GLfloat specref[] = { 1, 1, 1, 1 };
	glEnable(GL_LIGHTING);
	glLightfv(GL_LIGHT0, GL_AMBIENT, ambient);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse);
	glLightfv(GL_LIGHT0, GL_SPECULAR, specular);
	glEnable(GL_LIGHT0);

	glEnable(GL_COLOR_MATERIAL);
	glMaterialfv(GL_FRONT, GL_SPECULAR, specref);
	glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);
	glMateriali(GL_FRONT, GL_SHININESS, 128);

	//����Ƿ���Կ������ز���
	//��Ҫ�Կ�֧�֣��Կ���Ҫ��������
	GLint buffers, samples;
	glGetIntegerv(GL_SAMPLE_BUFFERS, &buffers);
	glGetIntegerv(GL_SAMPLES, &samples);
	printf("buffers = %d\nsamples = %d\n", buffers, samples);

	//���ö��ز���
	glEnable(GL_MULTISAMPLE);
}

void ReflectionTest::display(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(0.0, 150.0, 300.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);

	//���ù���
	glEnable(GL_LIGHTING);
	glLightfv(GL_LIGHT0, GL_POSITION, fLightPos);

	//����һ��СԲ������Դ
	glPushMatrix();
	glTranslatef(fLightPos[0], fLightPos[1], fLightPos[2]);
	glColor3f(1, 1, 0);
	glutSolidSphere(5, 10, 10);
	glPopMatrix();
	
	glPushMatrix();
	glColor3f(1.0, 1.0, 1.0);
	glTranslatef(0, 50, 0);
	glColor3f(1, 0, 0);
	glutSolidSphere(50, 50, 50);
	glPopMatrix();

	//���Ʒ���ĵ�Ӱ
	glLightfv(GL_LIGHT0, GL_POSITION, fLightPosMirror);
	glPushMatrix();
	glFrontFace(GL_CW);
	glScalef(1, -1, 1);
	glTranslatef(0, 50, 0);
	glColor3f(1, 0, 0);
	glutSolidSphere(50, 50, 50);
	glFrontFace(GL_CCW);
	glPopMatrix();



	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glColor4f(1.0, 1.0, 1.0, 0.8);
	//�򿪿���ݣ�����һЩ���⣬�����м�������� ,�Ƽ�ʹ�ö��ز��������
	//glEnable(GL_POLYGON_SMOOTH);
	//���棬������ɫ���
	glBegin(GL_QUADS);
	glNormal3f(0, 1, 0);
	glVertex3f(-150, 0, -150);
	glVertex3f(-150, 0, 150);
	glVertex3f(150, 0, 150);
	glVertex3f(150, 0, -150);
	glEnd();

	//�رտ����
	//glDisable(GL_POLYGON_SMOOTH);
	glDisable(GL_BLEND);

	glFlush();
	glutSwapBuffers();
}

void ReflectionTest::reshape(GLint w, GLint h)
{
	//���ֻ��Ƴ���������Σ���ʼ��λ�ڴ��ڵ�����
	GLint newW = w > h ? h : w;
	glViewport((w - newW) / 2, (h - newW) / 2, (GLsizei)newW, (GLsizei)newW);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	//glFrustum(-1.0, 1.0, -1.0, 1.0, 1.5, 20);
	gluPerspective(80.0, 1.0, 1.5, 450);
}