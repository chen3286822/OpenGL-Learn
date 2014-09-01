#include "stdafx.h"
#include "Cube.h"

void CubeTest::init(void)
{
	glewInit();
	glClearColor(0.0, 0.0, 0.0, 0.0);/* select clearing color   */
	//着色模式，GL_SMOOTH使用插值方式着色，GL_FLAT使用顶点颜色数组中最后若干颜色着色
	glShadeModel(GL_FLAT);
}

void CubeTest::reshape(GLint w, GLint h)
{
	//保持绘制场景不会变形，且始终位于窗口的中央
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

	//对立方体进行变换，先沿x轴移动5，再绕z轴逆时针旋转30度
	//模型变换矩阵为 C，每次变换后相当于C*M, C*M*N
	//最后应用到模型顶点上，C*M*N*v，相当于C*(M*(N*v))
	//其实是变换N先应用于顶点v，故实际调用变换函数的顺序与想要实现的变换是相反的
	glRotatef(30.0, 0.0, 0.0, 1.0);
	glTranslatef(5.0, 0.0, 0.0);
	glutWireCube(1.0);

	//让一三角形绕其一顶点旋转45度
	glLoadIdentity();
	gluLookAt(0.0, 0.0, 10.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
	glTranslatef(3.0, 0.0, 0.0);
	glRotatef(45.0, 1.0, 0.0, 0.0);
	glTranslatef(-3.0, 0.0, 0.0);
	glBegin(GL_TRIANGLES);
	glVertex3f(0.0, 0.0, 0.0);
	glVertex3f(3.0, 0.0, 0.0);
	glVertex3f(3.0, 3.0, 0.0);
	glEnd();

	glFlush();
	glutSwapBuffers();
}