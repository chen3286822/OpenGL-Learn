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
	//使用微弱环境光，使物体可见
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, ambientLight);

	GLfloat specular[] = { 1.0, 1.0, 1.0, 1.0 };
	GLfloat spotDir[] = { 0, -1, 0, 0 };
	
	GLfloat specref[] = { 1, 1, 1, 1 };
	glLightfv(GL_LIGHT0, GL_SPECULAR, specular);
	glLightfv(GL_LIGHT0, GL_SPOT_DIRECTION, spotDir);
	glLightf(GL_LIGHT0, GL_SPOT_CUTOFF, 85.0f);
	glLightfv(GL_LIGHT0, GL_POSITION, lightPos);
	glEnable(GL_LIGHT0);

	//启用颜色追踪
	glEnable(GL_COLOR_MATERIAL);
	//多边形正面的材质环境和散射颜色，追踪glColor
	glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);
	//设置材质镜面反射属性
	glMaterialfv(GL_FRONT, GL_SPECULAR, specref);
	//设置镜面亮点大小和集中值
	glMateriali(GL_FRONT, GL_SHININESS, 50);

	//取3个平面上的点
	M3DVector3f points[3] = { { -100, -100, -100 },
	{ -100, -100, 100 },
	{ 100, -100, 100 } };

	M3DVector4f vPlaneEquation;
	//取得平面方程
	m3dGetPlaneEquation(vPlaneEquation, points[0], points[1], points[2]);
	//根据光源位置、平面方程得出阴影矩阵
	m3dMakePlanarShadowMatrix(shadowMat, vPlaneEquation, lightPos);
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

	//启用光照
	glEnable(GL_LIGHTING);
	glLightfv(GL_LIGHT0, GL_POSITION, lightPos);

	//绘制一个小圆球代替光源
	glPushMatrix();
	glTranslatef(lightPos[0], lightPos[1], lightPos[2]);
	glColor3f(1, 1, 0);
	glutSolidSphere(5, 10, 10);
	glPopMatrix();

	//地面
	glColor3f(1.0, 1.0, 1.0);
	glBegin(GL_QUADS);
	glNormal3f(0, 1, 0);
	glVertex3f(-100, -100, -100);
	glVertex3f(-100, -100, 100);
	glVertex3f(100, -100, 100);
	glVertex3f(100, -100, -100);
	glEnd();

	glutSolidSphere(50, 50, 50);

	//禁用光照，绘制阴影
	glDisable(GL_LIGHTING);
	//禁用深度测试，因为阴影会绘制到地面上，保持阴影后绘制
	glDisable(GL_DEPTH_TEST);
	//保存矩阵状态
	glPushMatrix();

	//乘以阴影矩阵
	glMultMatrixf((GLfloat*)shadowMat);
	//阴影颜色
	glColor3f(0, 0, 0);
	//绘制球体阴影
	glutSolidSphere(50, 50, 50);
	//恢复矩阵
	glPopMatrix();

	//恢复深度测试
	glEnable(GL_DEPTH_TEST);

	glFlush();
	glutSwapBuffers();
}