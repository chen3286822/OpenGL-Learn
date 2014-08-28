#include "stdafx.h"
#include "Shadow.h"

void ShadowTest::init(void)
{
	glewInit();
	glClearColor(0.0, 0.0, 0.0, 0.0);/* select clearing color   */
	glShadeModel(GL_SMOOTH);
	glEnable(GL_DEPTH_TEST);
	glFrontFace(GL_CCW);
	glEnable(GL_CULL_FACE);
}

void ShadowTest::reshape(GLint w, GLint h)
{
	//保持绘制场景不会变形，且始终位于窗口的中央
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

	//地面
	glColor3f(1.0, 1.0, 1.0);
	glBegin(GL_QUADS);
	glVertex3f(-100, -100, -100);
	glVertex3f(-100, -100, 100);
	glVertex3f(100, -100, 100);
	glVertex3f(100, -100, -100);
	glEnd();

	glutSolidSphere(50, 50, 50);

	glFlush();
}

void ShadowTest::makeShadowMatrix(GLfloat* vPoints[3], GLfloat* lightPos, GLfloat* mat)
{

}