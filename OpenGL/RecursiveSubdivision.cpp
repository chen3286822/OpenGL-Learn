#include "stdafx.h"
#include "RecursiveSubdivision.h"

#define X 52.573
#define Z 85.065
void RecursiveSubdivisionTest::init(void)
{
	glewInit();
	glClearColor(0.0, 0.0, 0.0, 0.0);/* select clearing color   */
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	//glOrtho(-10.0, 10.0, -10.0, 10.0, -100.0, 100.0);/* initialize viewing values   */
	
	//开启深度测试，防止位于后面的三角形面由于后绘制而挡在前面
	glEnable(GL_DEPTH_TEST);
	glShadeModel(GL_SMOOTH);

	//剔除背面
	glFrontFace(GL_CCW);
	glEnable(GL_CULL_FACE);

	//开启光照
	 glEnable(GL_LIGHTING);
	
	GLfloat ambientLight[] = { 0.2, 0.2, 0.2, 1.0 };
	GLfloat diffuseLight[] = { 0.8, 0.8, 0.8, 1.0 };
	GLfloat specular[] = { 1.0, 1.0, 1.0, 1.0 };
	GLfloat specularRed[] = { 1.0, 0.0, 0.0, 1.0 };
	//射灯方向
	GLfloat spotDir[] = { 0.0, 0.0, -1.0, 0.0 };

	//材质的反射属性
	GLfloat specref[] = { 1.0, 1.0, 1.0, 1.0 };

	//使用环境光
	//glLightModelfv(GL_LIGHT_MODEL_AMBIENT, ambientLight);
	//设置光源
	glLightfv(GL_LIGHT0, GL_AMBIENT, ambientLight);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuseLight);
	glLightfv(GL_LIGHT0, GL_SPECULAR, specular);
	glEnable(GL_LIGHT0);

	glLightfv(GL_LIGHT1, GL_SPECULAR, specularRed);
	glLightfv(GL_LIGHT1, GL_SPOT_DIRECTION, spotDir);
	glLightf(GL_LIGHT1, GL_SPOT_CUTOFF, 85.0f);
	glEnable(GL_LIGHT1);
	

	//启用颜色追踪
	glEnable(GL_COLOR_MATERIAL);
	//多边形正面的材质环境和散射颜色，追踪glColor
	glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);
	//设置材质镜面反射属性
	glMaterialfv(GL_FRONT, GL_SPECULAR, specref);
	//设置镜面亮点大小和集中值
	glMateriali(GL_FRONT, GL_SHININESS, 50);
}

void RecursiveSubdivisionTest::reshape(GLint w, GLint h)
{
	GLint length = w > h ? h : w;
	glViewport(0, 0, (GLsizei)length, (GLsizei)length);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-100.0, 100.0, -100.0, 100.0, -100.0, 100.0);

	//放置光源
	GLfloat lightPos[] = { 0.0, 0.0, 200.0, 1.0 };
	glLightfv(GL_LIGHT0, GL_POSITION, lightPos);

	GLfloat lightPos2[] = { 150.0, 150.0, 200.0, 1.0 };
	glLightfv(GL_LIGHT1, GL_POSITION, lightPos2);
}

void RecursiveSubdivisionTest::keyboard(GLubyte key, GLint x, GLint y)
{
	switch (key)
	{
	case 0x031:
		glEnable(GL_LIGHT0);
		glEnable(GL_LIGHT1);
		break;
	case 0x032:
		glDisable(GL_LIGHT0);
		glEnable(GL_LIGHT1);
		break;
	default:
		glEnable(GL_LIGHT0);
		glDisable(GL_LIGHT1);
		break;
	}
	glutPostRedisplay();
}

void RecursiveSubdivisionTest::normalizeToRadius(GLfloat* v, GLfloat r)
{
	GLfloat normL = sqrt(v[0] * v[0] + v[1] * v[1] + v[2] * v[2]);
	v[0] = v[0] * r /normL;
	v[1] = v[1] * r / normL;
	v[2] = v[2] * r / normL;
}

void RecursiveSubdivisionTest::computeNormal(GLfloat* v1, GLfloat* v2, GLfloat* v3, GLfloat* norm)
{
	//计算法线向量
	GLfloat vec1[3], vec2[3];
	for (int j = 0; j < 3; ++j)
	{
		vec1[j] = v1[j] - v2[j];
		vec2[j] = v2[j] - v3[j];
	}
	//v1 和 v2 叉积得到面的法线向量
	norm[0] = vec1[1] * vec2[2] - vec1[2] * vec2[1];
	norm[1] = vec1[2] * vec2[0] - vec1[0] * vec2[2];
	norm[2] = vec1[0] * vec2[1] - vec1[1] * vec2[0];
	// 单位化法线向量
	normalizeToRadius(norm);
}

void RecursiveSubdivisionTest::drawTriangle(GLfloat* v1, GLfloat* v2, GLfloat* v3)
{
	GLfloat tmp[3];
	//computeNormal(v1, v2, v3, norm);
	
	glBegin(GL_TRIANGLES);
	//glNormal3fv(norm);
	//使用每个顶点作为法线向量
	memcpy(tmp, v1, 3 * sizeof(GLfloat));
	normalizeToRadius(tmp);
	glNormal3fv(tmp);
	glVertex3fv(v1);
	memcpy(tmp, v2, 3 * sizeof(GLfloat));
	normalizeToRadius(tmp);
	glNormal3fv(tmp);
	glVertex3fv(v2);
	memcpy(tmp, v3, 3 * sizeof(GLfloat));
	normalizeToRadius(tmp);
	glNormal3fv(tmp);
	glVertex3fv(v3);
	glEnd();
}

void RecursiveSubdivisionTest::subDivision(GLfloat* v1, GLfloat* v2, GLfloat* v3, GLint depth)
{
	GLfloat v12[3], v23[3], v13[3];

	if (depth == 0)
	{
		drawTriangle(v1, v2, v3);
		return;
	}

	for (GLint i = 0; i < 3; ++i)
	{
		v12[i] = (v1[i] + v2[i]) / 2;
		v23[i] = (v2[i] + v3[i]) / 2;
		v13[i] = (v1[i] + v3[i]) / 2;
	}
	//把生成的中点位置规范化，使其落在半径为100的圆上
	normalizeToRadius(v12, 100);
	normalizeToRadius(v23, 100);
	normalizeToRadius(v13, 100);
	subDivision(v1, v12, v13, depth - 1);
	subDivision(v2, v23, v12, depth - 1);
	subDivision(v3, v13, v23, depth - 1);
	subDivision(v12, v23, v13, depth - 1);
}

void RecursiveSubdivisionTest::display(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);/* clear all pixels   */

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	//绘制一个20面体
	static GLfloat vData[12][3] =
	{
		{ -X, 0.0, Z }, { X, 0.0, Z }, { -X, 0.0, -Z }, { X, 0.0, -Z },
		{ 0.0, Z, X }, { 0.0, Z, -X }, { 0.0, -Z, X }, { 0.0, -Z, -X },
		{ Z, X, 0.0 }, { -Z, X, 0.0 }, { Z, -X, 0.0 }, { -Z, -X, 0.0 }
	};
	static GLuint tindices[20][3] =
	{
		{ 1, 4, 0 }, { 4, 9, 0 }, { 4, 5, 9 }, { 8, 5, 4 }, { 1, 8, 4 },
		{ 1, 10, 8 }, { 10, 3, 8 }, { 8, 3, 5 }, { 3, 2, 5 }, { 3, 7, 2 },
		{ 3, 10, 7 }, { 10, 6, 7 }, { 6, 11, 7 }, { 6, 0, 11 }, { 6, 1, 0 },
		{ 10, 1, 6 }, { 11, 0, 9 }, { 2, 11, 9 }, { 5, 2, 9 }, { 11, 2, 7 },
	};

	glColor3f(0.0f, 0.7f, 0.0f);
	for (int i = 0; i < 20; i++)
	{
		subDivision(&vData[tindices[i][0]][0], &vData[tindices[i][1]][0], &vData[tindices[i][2]][0], 2);
	}

	//glutSolidSphere(30.0f, 30.0f, 30.0f);

// 	GLfloat v1[3], v2[3], v3[3], norm[3];
// 	v1[0] = X;
// 	v1[1] = 0;
// 	v1[2] = Z;
// 	v2[0] = 0;
// 	v2[1] = Z;
// 	v2[2] = X;
// 	v3[0] = -X;
// 	v3[1] = 0;
// 	v3[2] = Z;
// 	computeNormal(v1, v2, v3, norm);
// 	glBegin(GL_TRIANGLES);
// 	glNormal3fv(norm);
// 	glVertex3fv(v1);
// 	glVertex3fv(v2);
// 	glVertex3fv(v3);
// 	glEnd();

//  	glBegin(GL_QUADS);
//  	glNormal3f(0, 0, 1);
//  	glVertex3f(-50, 50, 50);
//  	//glNormal3f(0, 0, 1);
//  	glVertex3f(-50, -50, 50);
//  	//glNormal3f(0, 0, 1);
//  	glVertex3f(50, -50,50);
//  	//glNormal3f(0, 0, 1);
//  	glVertex3f(50, 50, 50);
//  	glEnd();


	//使用glDrawElements 一次性绘制所有面
// 	glEnableClientState(GL_VERTEX_ARRAY);
// 	glEnableClientState(GL_NORMAL_ARRAY);
// 	glVertexPointer(3, GL_FLOAT, 0, points);
// 	glNormalPointer(GL_FLOAT, 0, normal);
// 	glDrawElements(GL_QUADS, 6, GL_UNSIGNED_INT, index);
// 	glDisableClientState(GL_VERTEX_ARRAY);
// 	glDisableClientState(GL_NORMAL_ARRAY);
	glFlush();/* start processing buffered OpenGL routines   */

	glutSwapBuffers();
}