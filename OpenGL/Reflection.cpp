#include "stdafx.h"
#include "Reflection.h"

GLfloat ReflectionTest::fLightPos[4] = {0, 100, 0, 1};
GLfloat ReflectionTest::fLightPosMirror[4] = {0, -100, 0, 1};

void ReflectionTest::init(void)
{
	glewInit();
	glClearColor(0.0, 0.0, 0.0, 0.0);

	glEnable(GL_DEPTH_TEST);
	glFrontFace(GL_CCW);
	glEnable(GL_CULL_FACE);
	glEnable(GL_LIGHTING);

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
}

void ReflectionTest::display(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(0.0, 50.0, 300.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);

	//启用光照
	glEnable(GL_LIGHTING);
	glLightfv(GL_LIGHT0, GL_POSITION, fLightPos);

	//绘制一个小圆球代替光源
	glPushMatrix();
	glTranslatef(fLightPos[0], fLightPos[1], fLightPos[2]);
	glColor3f(1, 1, 0);
	glutSolidSphere(5, 10, 10);
	glPopMatrix();

	glColor3f(1.0, 1.0, 1.0);
	glutSolidSphere(50, 50, 50);

	//地面
	glBegin(GL_QUADS);
	glNormal3f(0, 1, 0);
	glVertex3f(-100, -100, -100);
	glVertex3f(-100, -100, 100);
	glVertex3f(100, -100, 100);
	glVertex3f(100, -100, -100);
	glEnd();

	//绘制反射的倒影
	//glDisable(GL_LIGHTING);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glLightfv(GL_LIGHT0, GL_POSITION, fLightPosMirror);
	glPushMatrix();
	glFrontFace(GL_CW);
	glScalef(1, -1, 1);
	glutSolidSphere(50, 50, 50);
	glFrontFace(GL_CCW);
	glPopMatrix();
	glDisable(GL_BLEND);
	//glEnable(GL_LIGHTING);

	glFlush();
	glutSwapBuffers();
}

void ReflectionTest::reshape(GLint w, GLint h)
{
	//保持绘制场景不会变形，且始终位于窗口的中央
	GLint newW = w > h ? h : w;
	glViewport((w - newW) / 2, (h - newW) / 2, (GLsizei)newW, (GLsizei)newW);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	//glFrustum(-1.0, 1.0, -1.0, 1.0, 1.5, 20);
	gluPerspective(60.0, 1.0, 1.5, 350);
}