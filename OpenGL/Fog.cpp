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

	//��Դ���
	GLfloat ambient[] = { 0.25f, 0.25f, 0.25f, 1.0f };
	GLfloat specref[] = { 1, 1, 1, 1 };
	GLfloat diffuse[] = { 0.25f, 0.25f, 0.25f, 1.0f };
	GLfloat specular[] = { 1.0f, 1.0f, 1.0f, 1.0f };
	GLfloat position[] = { 0, 400, 0, 0 };
	//������
	glEnable(GL_LIGHTING);
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, nolight);
	glLightfv(GL_LIGHT0, GL_AMBIENT, ambient);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse);
	glLightfv(GL_LIGHT0, GL_SPECULAR, specular);
	glLightfv(GL_LIGHT0, GL_POSITION, position);
	glEnable(GL_LIGHT0);

	//������ʷ���
	glEnable(GL_COLOR_MATERIAL);
	glMaterialfv(GL_FRONT, GL_SPECULAR, specref);
	glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);
	glMateriali(GL_FRONT, GL_SHININESS, 128);

	//��
	glEnable(GL_FOG);
	glFogfv(GL_FOG_COLOR, nolight);
	glFogf(GL_FOG_START, 20);
	glFogf(GL_FOG_END, 1000);
	glFogi(GL_FOG_MODE, GL_LINEAR);

	//ȡ3��ƽ���ϵĵ�
	//��Ϊ������Ӱ��Ҫ�ر���Ȳ��ԣ���������Ƶ���Ӱ�����ڵ���ǰ���Ƶ�����
	//������ȡƽ����΢���ϵĵ㣬�����õ�����Ӱ������΢������ƽ����
	//�Ͳ��ùر���Ȳ�����
	M3DVector3f points[3] = { { -100, -99.5, -100 },
	{ -100, -99.5, 100 },
	{ 100, -99.5, 100 } };

	M3DVector4f vPlaneEquation;
	//ȡ��ƽ�淽��
	m3dGetPlaneEquation(vPlaneEquation, points[0], points[1], points[2]);
	//���ݹ�Դλ�á�ƽ�淽�̵ó���Ӱ����
	m3dMakePlanarShadowMatrix(shadowMat, vPlaneEquation, position);

}

void FogTest::drawSphere(GLfloat* pos)
{
	glPushMatrix();
	glTranslatef(pos[0], pos[1], pos[2]);
	glutSolidSphere(20, 30, 30);
	glPopMatrix();

	//����С����Ӱ
	glDisable(GL_LIGHTING);
	glPushMatrix();
	//������Ӱ����
	glMultMatrixf((GLfloat*)shadowMat);
	glTranslatef(pos[0], pos[1], pos[2]);
	//��Ӱ��ɫ
	glColor3f(0, 0, 0);
	//����������Ӱ
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

	//���Ƶ���
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
	//���ֻ��Ƴ���������Σ���ʼ��λ�ڴ��ڵ�����
	GLint newW = w > h ? h : w;
	glViewport((w - newW) / 2, (h - newW) / 2, (GLsizei)newW, (GLsizei)newW);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	//glFrustum(-1.0, 1.0, -1.0, 1.0, 1.5, 20);
	gluPerspective(80.0, 1.0, 1.5, 1000);
}