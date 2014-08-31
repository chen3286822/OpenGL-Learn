#include "stdafx.h"
#include "Fog.h"

void FogTest::init(void)
{
	GLfloat nolight[] = { 0, 0, 0, 0 };
	

	glewInit();
	glClearColor(nolight[0], nolight[1], nolight[2], nolight[3]);

	glEnable(GL_DEPTH_TEST);
	glFrontFace(GL_CCW);
	glCullFace(GL_BACK);
	glEnable(GL_CULL_FACE);

	//光源相关
	GLfloat ambient[] = { 0.25f, 0.25f, 0.25f, 1.0f };
	GLfloat specref[] = { 1, 1, 1, 1 };
	GLfloat diffuse[] = { 0.25f, 0.25f, 0.25f, 1.0f };
	GLfloat specular[] = { 1.0f, 1.0f, 1.0f, 1.0f };
	GLfloat position[] = { 0, 400, 0, 0 };
	//环境光
	glEnable(GL_LIGHTING);
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, nolight);
	glLightfv(GL_LIGHT0, GL_AMBIENT, ambient);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse);
	glLightfv(GL_LIGHT0, GL_SPECULAR, specular);
	glLightfv(GL_LIGHT0, GL_POSITION, position);
	glEnable(GL_LIGHT0);

	//物体材质反射
	glEnable(GL_COLOR_MATERIAL);
	glMaterialfv(GL_FRONT, GL_SPECULAR, specref);
	glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);
	glMateriali(GL_FRONT, GL_SHININESS, 128);

	//雾
	glEnable(GL_FOG);
	glFogfv(GL_FOG_COLOR, nolight);
	glFogf(GL_FOG_START, 20);
	glFogf(GL_FOG_END, 1000);
	glFogi(GL_FOG_MODE, GL_LINEAR);

	//取3个平面上的点
	//因为绘制阴影需要关闭深度测试，这样后绘制的阴影可能遮挡先前绘制的球体
	//故这里取平面稍微向上的点，这样得到的阴影可以稍微悬浮在平面上
	//就不用关闭深度测试了
	M3DVector3f points[3] = { { -100, -99.5, -100 },
	{ -100, -99.5, 100 },
	{ 100, -99.5, 100 } };

	M3DVector4f vPlaneEquation;
	//取得平面方程
	m3dGetPlaneEquation(vPlaneEquation, points[0], points[1], points[2]);
	//根据光源位置、平面方程得出阴影矩阵
	m3dMakePlanarShadowMatrix(shadowMat, vPlaneEquation, position);

}

void FogTest::drawSphere(GLfloat* pos)
{
	glPushMatrix();
	glTranslatef(pos[0], pos[1], pos[2]);
	glutSolidSphere(20, 30, 30);
	glPopMatrix();

	//绘制小球阴影
	glDisable(GL_LIGHTING);
	glPushMatrix();
	//乘以阴影矩阵
	glMultMatrixf((GLfloat*)shadowMat);
	glTranslatef(pos[0], pos[1], pos[2]);
	//阴影颜色
	glColor3f(0, 0, 0);
	//绘制球体阴影
	glutSolidSphere(20, 30, 30);
	glColor3f(1, 1, 1);
	glPopMatrix();
	glEnable(GL_LIGHTING);
}

void FogTest::display(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(0.0, 150.0, 300.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);

	//绘制地面
	glColor3f(1.0, 1.0, 1.0);
	glBegin(GL_QUADS);
	glNormal3f(0, 1, 0);
	glVertex3f(-300, -100, -600);
	glVertex3f(-300, -100, 100);
	glVertex3f(300, -100, 100);
	glVertex3f(300, -100, -600);
	glEnd();

	GLfloat spherePos[3][3] = {
			{-50, 0, 50}, {0, 0, 0}, {100, 0, -450}
	};
	for (int i = 0; i < 3; ++i)
		drawSphere(spherePos[i]);

	glFlush();
	glutSwapBuffers();
}

void FogTest::reshape(GLint w, GLint h)
{
	//保持绘制场景不会变形，且始终位于窗口的中央
	GLint newW = w > h ? h : w;
	glViewport((w - newW) / 2, (h - newW) / 2, (GLsizei)newW, (GLsizei)newW);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	//glFrustum(-1.0, 1.0, -1.0, 1.0, 1.5, 20);
	gluPerspective(80.0, 1.0, 1.5, 1000);
}